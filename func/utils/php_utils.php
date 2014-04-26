
if ($_REQUEST['delete_rows'])
 	{
 		$passed_rows=array();
 		$temp=$_REQUEST['rows'];
 		//$passed_rows = unserialize($_SESSION($del_rows));
 		$passed_rows=unserialize($temp);
 		//$data = rawurldecode($data);
 		npr($passed_rows);
 		$count=0;
 		foreach ($passed_rows as $table_name)
 		{
			$assets_sql = "DELETE FROM pf_table_data WHERE pf_table_name = '$table_name'";	
			$table_sql = "DELETE FROM pf_table_ports WHERE pf_table_name = '$table_name'";
			notice($table_name);
			$db=query($assets_sql);
			$db=query($table_sql); //delete the table
 		 	if($db->get_error())
 			{
 				$count++;
 			}
 		}
 		if ($count == 0)
 		{
 			notice("The deletion succesful");
 		}
 		unset($passed_rows);
 	}
 	
	if(count($delete_rows)>0)
	{
		//notice("The selected rows will be processed now");
		$rules_array = array();
		$table_rules=table("name=rules","label= Firewall rules associated with the selected tables:");
		$table_rules->column("name=rule","label=Rule");
		foreach($delete_rows as $row)
		{ 
			$rules=extract_firewall_rules(false,true);
			foreach($rules as $thisid=>$rule)
			{
				if(!strstr($rule['rule'],"<".$row.">"))
				{
					unset($rules[$thisid]);
				}
			}
			if($rules) 
			{
				//notice("Following Rules associated with this table. Still Delete it??");	
				$table_rules->data($rules);
			}
		}
		if ($table_rules->get_num_rows()>0)
			$table_rules->attach();
			notice($_SERVER['REQUEST_URI']);
		$form =form("action={$_SERVER['REQUEST_URI']}",
					"name=delet_rows", 
					"method=post");
		$form->button("name=submit","type=submit","label=Yes delete the tables.");
		$data=serialize($delete_rows);
		$form->hidden("name=delete_rows", "value=1");
		//$form->hidden("name=rows", "value=<?=$data");
		$form->hidden("name=rows", "value=$data");
		$form->attach();
		if ($form->posted())
		{
		
		}
	}
-- 



