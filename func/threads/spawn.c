/*******************************************************************/
/*******************************************************************/
/*                                                                 */
/* FUNCTION:  This program acts as a parent to a child program.    */
/*                                                                 */
/* LANGUAGE:  ILE C for OS/400                                     */
/*                                                                 */
/* APIs USED: putenv(), spawn(), wait(), waitpid()                 */
/*                                                                 */
/*******************************************************************/
/*******************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <spawn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAP_NUM    5
#define ARGV_NUM   6
#define ENVP_NUM   2
#define CHILD_PGM  "QGPL/CHILD"

extern char **environ;

/* This is a parent program that will use spawn() in 3 different     */
/* ways for 3 different children.  A file is created that is         */
/* written to, both by the parent and the 3 children.  The end result*/
/* of the file will look something like the following:               */
/*     Parent writes    Child writes                                 */
/*     -------------    ---------------------------------------      */
/*           1          argv[0]  getppid()  getpgrp()  getpid()      */
/*           2          argv[0]  getppid()  getpgrp()  getpid()      */
/*           3          argv[0]  getppid()  getpgrp()  getpid()      */
/* The parent uses wait() or waitpid() to wait for a given child to  */
/* return and to retrieve the resulting status of the child when it  */
/* does return.                                                      */
int main(int argc, char *argv[])
{
    int    rc;                          /* API return code           */
    int    fd, fd_read;                 /* parent file descriptors   */
    char   fd_str[4];                  /* file descriptor string     */
    char   f_path_name[] = "A_File";             /* file pathname    */
    int    buf_int;                     /* write(), read() buffer    */
    char   buf_pgm_name[22];           /* read() program name buffer */
    char   spw_path[] = "/QSYS.LIB/QGPL.LIB/CHILD.PGM";
                                        /* spawn() *path             */
    int    spw_fd_count;                /* spawn() fd_count          */
    int    spw_fd_map[MAP_NUM];
                                         /* spawn() fd_map[]         */
    struct inheritance spw_inherit;     /* spawn() *inherit          */
    char  *spw_argv[ARGV_NUM];
                                     /* spawn() *argv[]              */
    char  *spw_envp[ENVP_NUM];
                                     /* spawn() *envp[]              */
    int    seq_num;                     /* sequence number           */
    char   seq_num_str[4];             /* sequence number string     */
    pid_t  pid;                         /* parent pid                */
    char   pid_str[11];                /* parent pid string          */
    pid_t  pgrp;                        /* parent process group      */
    char   pgrp_str[11];             /* parent process group string  */
    pid_t  spw_child_pid[3];           /* 3 spawn() child pid        */
    pid_t  wt_child_pid[3];          /* 3 wait()/waitpid() child pid */
    int    wt_stat_loc[3];
                                      /* 3 wait()/waitpid() *stat_loc*/
    int    wt_pid_opt = 0;              /* waitpid() option          */
    char   env_return_val[16];
                                      /* environ var "return_val="   */

    memset(&spw_inherit,0x00,sizeof(spw_inherit));

    /* Get the pid and pgrp for the parent.                          */
    pid = getpid();
    pgrp = getpgrp();

    /* Format the pid and pgrp value into null-terminated strings.   */
    sprintf(pid_str, "%d", pid);
    sprintf(pgrp_str, "%d", pgrp);

    /* Create a file and maintain the file descriptor.               */
    fd = creat(f_path_name, S_IRWXU);
    if (fd == -1)
      {
        printf("FAILURE: creat() with errno = %d\n",errno);
        return -1;
      }

    /* Format the file descriptor into null-terminated string.       */
    sprintf(fd_str, "%d", fd);

    /* Set the spawn() child arguments that are common for each      */
    /* child.                                                        */
    /* NOTE: The child will always get argv[0] in the                */
    /* LIBRARY/PROGRAM notation, but the                             */
    /* spawn() argv[0] (spw_argv[0]                                  */
    /* in this case) must be non-NULL in order to allow additional   */
    /* arguments.  For this example, the character pointer spw_path  */
    /* was chosen.                                                   */
    /* NOTE: The parent pid and the parent process group are passed  */
    /* to the child for demonstration purposes only.                 */
    spw_argv[0] = spw_path;
    spw_argv[1] = pid_str;
    spw_argv[2] = pgrp_str;
    spw_argv[4] = fd_str;
    spw_argv[5] = NULL;

    /* Write a '1' out to the file.                                  */
    buf_int = 1;
    write(fd, &buf_int, sizeof(int));

    /* The 1st spawn() will use simple inheritance for file          */
    /* descriptors (fd_map[] value is NULL).                         */
    spw_fd_count = 0;
    spw_inherit.pgroup = 0;
    seq_num = 1;
    sprintf(seq_num_str, "%d", seq_num);
    spw_argv[3] = seq_num_str;
    spw_envp[0] = NULL;
    spw_child_pid[0] = spawn(spw_path, spw_fd_count, NULL, &spw_inherit,
                             spw_argv, spw_envp);
    if (spw_child_pid[0] == -1)
      {
        printf("FAILURE: spawn() #1 with errno = %d\n",errno);
        close(fd);
        unlink(f_path_name);
        return -1;
      }

    /* NOTE: The parent can continue processing while the child is   */
    /* also processing.  In this example, though, the parent will    */
    /* simply /* wait() until the child finishes processing.         */

    /* Issue wait() in order to wait for the child to return.        */
    wt_child_pid[0] = wait(&wt_stat_loc[0]);
    if (wt_child_pid[0] == -1)
      {
        printf("FAILURE: wait() #1 with errno = %d\n",errno);
        close(fd);
        unlink(f_path_name);
        return -1;
      }

    /* Check to ensure the child's pid returned from spawn() is the  */
    /* same as the child's pid returned from wait(), for which       */
    /* status was returned.                                          */
    if ( (spw_child_pid[0] != wt_child_pid[0]) )
        printf("FAILURE: spawn() #1 and wait() #1 pid not the same\n");

    /* Check to ensure the child did not encounter an error          */
    /* condition.                                                    */
    if (WIFEXITED(wt_stat_loc[0]))
      {
        if (WEXITSTATUS(wt_stat_loc[0]) != 1)
            printf("FAILURE: wait() exit status = %d\n",
                   WEXITSTATUS(wt_stat_loc[0]));
      }
    else
        printf("FAILURE: unknown child #1 status\n");

    /* Write a '2' out to the file.                                  */
    buf_int = 2;
    write(fd, &buf_int, sizeof(int));

    /* The 2nd spawn() will use mapping for the file descriptor,     */
    /* along with the inheritance option to create a new process     */
    /* group for the child.                                          */
    spw_fd_count = 1;
    spw_fd_map[0] = fd;
    spw_inherit.pgroup = SPAWN_NEWPGROUP;
    seq_num = 2;
    sprintf(seq_num_str, "%d", seq_num);
    spw_argv[3] = seq_num_str;
    spw_envp[0] = NULL;
    spw_child_pid[1] = spawn(spw_path, spw_fd_count, spw_fd_map,
                             &spw_inherit, spw_argv, spw_envp);
    if (spw_child_pid[1] == -1)
      {
        printf("FAILURE: spawn() #2 with errno = %d\n",errno);
        close(fd);
        unlink(f_path_name);
        return -1;
      }

    /* NOTE: The parent can continue processing while the child is   */
    /* also processing.  In this example, though, the parent will    */
    /* simply waitpid() until the child finishes processing.         */

    /* Issue waitpid() in order to wait for the child to return.     */
    wt_child_pid[1] = waitpid(spw_child_pid[1], &wt_stat_loc[1],
                              wt_pid_opt);
    if (wt_child_pid[1] == -1)
      {
        printf("FAILURE: waitpid() #2 with errno = %d\n",errno);
        close(fd);
        unlink(f_path_name);
        return -1;
      }

    /* Check to ensure the child's pid returned from spawn() is the  */
    /* same as the child's pid returned from waitpid(), for which    */
    /* status was returned.                                          */
    if ( (spw_child_pid[1] != wt_child_pid[1]) )
        printf("FAILURE: spawn() #2 and waitpid() #2 pid not same\n");

    /* Check to ensure the child did not encounter an error          */
    /* condition.                                                    */
    if (WIFEXITED(wt_stat_loc[1]))
      {
        if (WEXITSTATUS(wt_stat_loc[1]) != 2)
            printf("FAILURE: waitpid() exit status = %d\n",
                   WEXITSTATUS(wt_stat_loc[1]));
      }
    else
        printf("FAILURE: unknown child #2 status\n");

    /* Write a '3' out to the file.                                  */
    buf_int = 3;
    write(fd, &buf_int, sizeof(int));

    /* The 3rd spawn() will use mapping for the file descriptors     */
    /* with some file descriptors designated as being closed         */
    /* (SPAWN_FDCLOSED) and the same parent file descriptor mapped   */
    /* to more than one child file descriptor.  In addition, an      */
    /* environment variable will be set and used by the child.       */
    spw_fd_count = 5;
    spw_fd_map[0] = SPAWN_FDCLOSED;
    spw_fd_map[1] = SPAWN_FDCLOSED;
    spw_fd_map[2] = fd;
    spw_fd_map[3] = SPAWN_FDCLOSED;
    spw_fd_map[4] = fd;
    spw_inherit.pgroup = 0;
    seq_num = 3;
    sprintf(seq_num_str, "%d", seq_num);
    spw_argv[3] = seq_num_str;
    strcpy(env_return_val,"return_val=3");
    rc = putenv(env_return_val);
    if (rc < 0)
      {
        printf("FAILURE: putenv() with errno = %d\n",errno);
        close(fd);
        unlink(f_path_name);
        return -1;
      }
    spw_child_pid[2] = spawn(spw_path, spw_fd_count, spw_fd_map,
                             &spw_inherit, spw_argv, environ);
    if (spw_child_pid[2] == -1)
      {
        printf("FAILURE: spawn() #3 with errno = %d\n",errno);
        close(fd);
        unlink(f_path_name);
        return -1;
      }

    /* The parent no longer needs to use the file descriptor, so it  */
    /* can close it, now that it has issued spawn().                 */
    rc = close(fd);
    if (rc != 0)
        printf("FAILURE: close(fd) with errno = %d\n",errno);

    /* NOTE: The parent can continue processing while the child is   */
    /* also processing.  In this example, though, the parent will    */
    /* simply wait() until the child finishes processing.            */

    /* Issue wait() in order to wait for the child to return.        */
    wt_child_pid[2] = wait(&wt_stat_loc[2]);
    if (wt_child_pid[2] == -1)
      {
        printf("FAILURE: wait() #3 with errno = %d\n",errno);
        unlink(f_path_name);
        return -1;
      }

    /* Check to ensure the child's pid returned from spawn() is the  */
    /* same as the child's pid returned from wait(), for which       */
    /* status was returned.                                          */
    if ( (spw_child_pid[2] != wt_child_pid[2]) )
        printf("FAILURE: spawn() #3 and wait() #3 pid not the same\n");

    /* Check to ensure the child did not encounter an error          */
    /* condition.                                                    */
    if (WIFEXITED(wt_stat_loc[2]))
      {
        if (WEXITSTATUS(wt_stat_loc[2]) != 3)
            printf("FAILURE: wait() exit status = %d\n",
                   WEXITSTATUS(wt_stat_loc[2]));
      }
    else
        printf("FAILURE: unknown child #3 status\n");

    /* Open the file for read to verify what the child wrote.        */
    fd_read = open(f_path_name, O_RDONLY);
    if (fd_read == -1)
      {
        printf("FAILURE: open() for read with errno = %d\n",errno);
        unlink(f_path_name);
        return -1;
      }

    /* Verify what child #1 wrote.                                   */
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != 1) )
        printf("FAILURE: read() #1\n");
    memset(buf_pgm_name,0x00,sizeof(buf_pgm_name));
    rc = read(fd_read, buf_pgm_name, strlen(CHILD_PGM));
    if ( (rc != strlen(CHILD_PGM)) ||
         (strcmp(buf_pgm_name,CHILD_PGM) != 0) )
        printf("FAILURE: read() child #1 argv[0]\n");
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != pid) )
        printf("FAILURE: read() child #1 getppid()\n");
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != pgrp) )
        printf("FAILURE: read() child #1 getpgrp()\n");
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != spw_child_pid[0]) ||
         (buf_int != wt_child_pid[0]) )
        printf("FAILURE: read() child #1 getpid()\n");

    /* Verify what child #2 wrote.                                   */
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != 2) )
        printf("FAILURE: read() #2\n");
    memset(buf_pgm_name,0x00,sizeof(buf_pgm_name));
    rc = read(fd_read, buf_pgm_name, strlen(CHILD_PGM));
    if ( (rc != strlen(CHILD_PGM)) ||
         (strcmp(buf_pgm_name,CHILD_PGM) != 0) )
        printf("FAILURE: read() child #2 argv[0]\n");
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != pid) )
        printf("FAILURE: read() child #2 getppid()\n");
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int == pgrp) )
        printf("FAILURE: read() child #2 getpgrp()\n");
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != spw_child_pid[1]) ||
         (buf_int != wt_child_pid[1]) )
        printf("FAILURE: read() child #2 getpid()\n");

    /* Verify what child #3 wrote.                                   */
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != 3) )
        printf("FAILURE: read() #3\n");
    memset(buf_pgm_name,0x00,sizeof(buf_pgm_name));
    rc = read(fd_read, buf_pgm_name, strlen(CHILD_PGM));
    if ( (rc != strlen(CHILD_PGM)) ||
         (strcmp(buf_pgm_name,CHILD_PGM) != 0) )
        printf("FAILURE: read() child #3 argv[0]\n");
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != pid) )
        printf("FAILURE: read() child #3 getppid()\n");
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != pgrp) )
        printf("FAILURE: read() child #3 getpgrp()\n");
    rc = read(fd_read, &buf_int, sizeof(int));
    if ( (rc != sizeof(int)) || (buf_int != spw_child_pid[2]) ||
         (buf_int != wt_child_pid[2]) )
        printf("FAILURE: read() child #3 getpid()\n");

    /* Attempt one more read() to ensure there is no more data.      */
    rc = read(fd_read, &buf_int, sizeof(int));
    if (rc != 0)
        printf("FAILURE: read() past end of data\n");

    /* The parent no longer needs to use the read() file descriptor, */
    /* so it can close it.                                           */
    rc = close(fd_read);
    if (rc != 0)
        printf("FAILURE: close(fd_read) with errno = %d\n",errno);

    /* Attempt one more wait() to ensure there are no more children. */
    wt_child_pid[0] = wait(&wt_stat_loc[0]);
    if ( (wt_child_pid[0] != -1) || (errno != ECHILD) )
        printf("FAILURE: ECHILD wait()\n");

    /* Clean up by performing unlink().                              */
    rc = unlink(f_path_name);
    if (rc != 0)
      {
        printf("FAILURE: unlink() with errno = %d\n",errno);
        return -1;
      }
    printf("completed successfully\n");
    return 0;
}

Child program

This program acts as a child to a parent program (see Parent program). This program demonstrates how a child program uses characteristics expressed through the use of spawn() in the parent program. The use of file descriptors, the creation of a new process group, arguments passed from the parent, and environment variables are demonstrated. The child program handles three distinct calls through the use of one of its arguments.

Use the CRTCMOD and CRTPGM commands to create this program (see Creating the parent and child programs).

This program is called by the spawn() function from the parent program. The program name must be CHILD and must be created into library QGPL, as indicated by the parent program. This program is not to be called directly.

/*******************************************************************/
/*******************************************************************/
/*                                                                 */
/* FUNCTION:  This program acts as a child to a parent program.    */
/*                                                                 */
/* LANGUAGE:  ILE C for OS/400                                     */
/*                                                                 */
/* APIs USED: getenv(), getpid(), getppid(), getpgrp()             */
/*                                                                 */
/*******************************************************************/
/*******************************************************************/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/* This is a child program that gets control from a parent program   */
/* that issues spawn().  This particular child program expects the   */
/* following 5 arguments (all are null-terminated strings):          */
/*     argv[0] - child program name                                  */
/*     argv[1] - parent pid (for demonstration only)                 */
/*     argv[2] - parent process group (for demonstration only)       */
/*     argv[3] - sequence number                                     */
/*     argv[4] - parent file descriptor                              */
/* If the child program encounters an error, it returns with a value */
/* greater than 50.  If the parent uses wait() or waitpid(), this    */
/* return value can be interrogated using the WIFEXITED and          */
/* WEXITSTATUS macros on the resulting wait() or waitpid()           */
/* *stat_loc field.                                                  */
int main(int argc, char *argv[])
{
    pid_t  p_pid;                    /* parent pid argv[1]           */
    pid_t  p_pgrp;                   /* parent process group argv[2] */
    int    seq_num;                  /* parent sequence num argv[3]  */
    int    fd;                       /* parent file desc argv[4]     */
    int    rc;                          /* API return code           */
    pid_t  pid;                         /* getpid() - child pid      */
    pid_t  ppid;                        /* getppid() - parent pid    */
    pid_t  pgrp;                        /* getpgrp() - process group */
    char  *env_return_val;           /* environ var for "return_val" */

    /* Get the pid, ppid, and pgrp for the child.                    */
    pid = getpid();
    ppid = getppid();
    pgrp = getpgrp();

    /* Verify 5 parameters were passed to the child.                 */
    if (argc != 5)
        return 60;

    /* Since the parameters passed to the child using spawn() are    */
    /* pointers to strings, convert the parent pid, parent process   */
    /* group, sequence number, and the file descriptor from strings  */
    /* to integers.                                                  */
    p_pid = atoi(argv[1]);
    p_pgrp = atoi(argv[2]);
    seq_num = atoi(argv[3]);
    fd = atoi(argv[4]);

    /* Verify the getpid() value of the parent is the same as the    */
    /* getppid() value of the child.                                 */
    if (p_pid != ppid)
        return 61;

    /* If the sequence number is 1, simple inheritance was used in   */
    /* this case.  First, verify the getpgrp() value of the parent   */
    /* is the same as the getpgrp() value of the child.  Next, the   */
    /* child will use the file descriptor passed in to write the     */
    /* child's values for argv[0], getppid(), getpgrp(),            */
    /* and getpid().  Finally, the child returns, which will satisfy */
    /* the parent's wait() or waitpid().                             */
    if (seq_num == 1)
      {
        if (p_pgrp != pgrp)
            return 70;
        rc = write(fd, argv[0], strlen(argv[0]));
        if (rc != strlen(argv[0]))
            return 71;
        rc = write(fd, &ppid, sizeof(pid_t));
        if (rc != sizeof(pid_t))
            return 72;
        rc = write(fd, &pgrp, sizeof(pid_t));
        if (rc != sizeof(pid_t))
            return 73;
        rc = write(fd, &pid, sizeof(pid_t));
        if (rc != sizeof(pid_t))
            return 74;
        return seq_num;
      }

    /* If the sequence number is 2, file descriptor mapping was used */
    /* in this case.  In addition, an inheritance option was used to */
    /* indicate this child will create a new process group.  First,  */
    /* verify the getpgrp() value of the parent is different than    */
    /* the getpgrp() value of the child.  Next, the child will use   */
    /* a literal value of '0' as the file descriptor (instead of the */
    /* parent's file descriptor passed in) since a known mapping was */
    /* performed by the parent.  This literal is used to write the   */
    /* child's values for argv[0], getppid(), getpgrp(),             */
    /* and getpid().  Finally, the child returns, which will satisfy */
    /* the parent's wait() or waitpid().                             */
    else if (seq_num == 2)
      {
        if (p_pgrp == pgrp)
            return 80;
        rc = write(0, argv[0], strlen(argv[0]));
        if (rc != strlen(argv[0]))
            return 81;
        rc = write(0, &ppid, sizeof(pid_t));
        if (rc != sizeof(pid_t))
            return 82;
        rc = write(0, &pgrp, sizeof(pid_t));
        if (rc != sizeof(pid_t))
            return 83;
        rc = write(0, &pid, sizeof(pid_t));
        if (rc != sizeof(pid_t))
            return 84;
        return seq_num;
      }

    /* If the sequence number is 3, file descriptor mapping was used */
    /* in this case.  In addition, an environment variable by the    */
    /* name of "return_val" was set with the desired return value.   */
    /* First, verify the getpgrp() value of the parent is the same   */
    /* as the getpgrp() value of the child.  Next, the child will    */
    /* use literal values of '2' and '4' as the file descriptor      */
    /* (instead of the parent's file descriptor passed in) since a   */
    /* known mapping was performed by the parent.  These literals    */
    /* are used to write the child's values for argv[0], getppid(),  */
    /* getpgrp(), and getpid().  Finally, getenv() is performed to   */
    /* retrieve the desired value to use on return, which will       */
    /* satisfy the parent's wait() or waitpid().                     */
    else if (seq_num == 3)
      {
        if (p_pgrp != pgrp)
            return 90;
        rc = write(4, argv[0], strlen(argv[0]));
        if (rc != strlen(argv[0]))
            return 91;
        rc = write(2, &ppid, sizeof(pid_t));
        if (rc != sizeof(pid_t))
            return 92;
        rc = write(4, &pgrp, sizeof(pid_t));
        if (rc != sizeof(pid_t))
            return 93;
        rc = write(2, &pid, sizeof(pid_t));
        if (rc != sizeof(pid_t))
            return 94;
        env_return_val = getenv("return_val");
        return (atoi(env_return_val));
      }

    /* If the sequence number is an unexpected value, return         */
    /* indicating an error.                                          */
    else
        return 99;
}

