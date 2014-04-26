#include<iostream>
#include <boost/thread/locks.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio/io_service.hpp>

class ThreadManager{

  public:

    ThreadManager(int size):
      _threadCount(size){

        _work.reset( new boost::asio::io_service::work(_io_service) );

        workerThreads();
      }

    ~ThreadManager()
    {
      _io_service.stop();
      _threads.join_all();
    }

    template<class A,class B, class C>
      void post(A func, B instance,C data);

 protected:

    int _threadCount;

    boost::asio::io_service _io_service;

    boost::thread_group _threads;

    boost::shared_ptr<boost::asio::io_service::work> _work;

    void workerThreads(){

      for(long x = 0 ; x < _threadCount ; ++x)
      {
        _threads.create_thread(boost::bind(&boost::asio::io_service::run,
              &_io_service));
      }
    }


};

template<class A,class B, class C>
void ThreadManager::post(A callback, B instance,C data){

  _io_service.post(
      boost::bind(callback,
        instance, data ));
}

class Data{

  public:

    Data(int jobSize)
    {
      _readValue = 0;
      _realValue = 0;
      int thrdId = 1;
      boost::thread th1(&Data::getValue,this,thrdId);
      ++thrdId;
      boost::thread th2(&Data::getValue,this,thrdId);

      _thrd = new ThreadManager(jobSize);
    }

  void getValue(int thrdId)
    {

       while(1)
       {
         std::string message;
         std::string value, threadId;

         char cValue[20] ;
         char cThrdId[20] ;
         sprintf( cValue, "%d", _readValue ) ;
         sprintf( cThrdId, "%d", thrdId ) ;
         value.assign( cValue ) ;
         threadId.assign( cThrdId ) ;

         message = "Thrd Id : " + threadId + " Value read : " + value;
         std::cout<<std::endl<<message<<std::endl;
         sleep(1);
       }
    }

    void updateValue(int count)
    {
      for(int x = 0; x < count ; ++x)
      {
        _thrd->post(&Data::setValue,this,x);
      }
    }

void setValue(int value)
    {
      boost::mutex::scoped_lock lock(_mutex);
      std::cout<<"Value to updated: "<<value<<std::endl;
      _realValue = value;
      _readValue = _realValue;
    }

  private:

    boost::mutex _mutex;
    ThreadManager* _thrd;

    int _readValue;
    int _realValue;
};

int main()
{
   Data inst(5);


   while(1)
   {
     inst.updateValue(3);
     sleep(5);
   }

  return 0;

}
