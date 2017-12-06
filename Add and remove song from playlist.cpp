void application::addSongToPlaylist()
{
 bool flag = false;
   do{
        string playlistName;
        string songName;
        cout<<"Enter the Playlist  Name"<<endl;
        cin>>playlistName;
 	    stringstream query;
        query<< "select PID from playList where userName = "<< '"'<<  username<<'"'<<"and playlistName = "
        <<'"'<<playlistName<<'"'<<";";
        MYSQL_RES* rset;
        MYSQL_ROW row;
        string authentication;
        if((mysql_query(db_conn, query.str().c_str()))==0)
        {
                 rset = mysql_use_result(db_conn);
                 row = mysql_fetch_row(rset);
                 authentication1 = row[0];
                 if(authentication1.compare("1") == 0)
                 {
                         mysql_free_result(rset);
             cout<< "Enter the song name you want to add to the playlist: "<< endl;
             cin>>songName;                       
		   	 stringstream queryone;
			 query1<< "select songName from song where songName = "<<'"' <<songName<<'"'<<";";
			
			 if((mysql_query(db_conn, query1.str().c_str()))==0)
			  {
	                         rset = mysql_use_result(db_conn);
	                         row = mysql_fetch_row(rset);
	                         authentication = row[0];
				             if(authentication.compare("0") == 0)		  	 
				             {
                                 stringstream query2;
			  		             query2 << "INSERT INTO playlistRecord(PID, songName)"
                                 << "values ("<<'"' << authentication1<< '"'<<','<<'"'<< songName << '"'<<");";
			  		             mysql_free_result(rset);                         
                          		 if((mysql_query(db_conn, query2.str().c_str()))==0)
                          		 {
                                                          cout<<"Song Added to playlist Sucessfully"<<endl;
                                                          flag = true;
                                  }else
                                       {
                                           cout<<mysql_error(db_conn)<<endl;
					                                     }
                             }
				             else
				                 {
					             cout<<"Song does not Exist"<<endl;
					             mysql_free_result(rset);
					             continue;
			                    }
                  }else
		               {	 
                        mysql_free_result(rset);
                       cout<<mysql_error(db_conn)<<endl;
				                     }
			
                 }
                 else
                 {	 mysql_free_result(rset);
                 	cout<<"Playlist Not found"<<endl;
                 	continue;
                 }
       	}else
	{
                cout<<mysql_error(db_conn)<<endl;
        }
      }while(flag == false);
}



void application::removeSongFromPlaylist()
{
 bool flag = false;
   do{
        string playlistName;
        string songName;
        cout<<"Enter the Playlist  Name"<<endl;
        cin>>playlistName;
 	    stringstream query;
        query<< "select PID from playList where userName = "<< '"'<<  username<<'"'<<"and playlistName = "
        <<'"'<<playlistName<<'"'<<";";
        MYSQL_RES* rset;
        MYSQL_ROW row;
        string authentication;
        if((mysql_query(db_conn, query.str().c_str()))==0)
        {
                 rset = mysql_use_result(db_conn);
                 row = mysql_fetch_row(rset);
                 authentication1 = row[0];
                 if(authentication1.compare("1") == 0)
                 {
                         mysql_free_result(rset);
             cout<< "Enter the song name you want to remove from the playlist: "<< endl;
             cin>>songName;                       
		   	 stringstream queryone;
			 query1<< "select songName from playlistRecord where songName = "<<'"' <<songName<<'"'<<"and PID = "
        <<'"'<<authentication1<<'"'<<";";
			
			 if((mysql_query(db_conn, query1.str().c_str()))==0)
			  {
	                         rset = mysql_use_result(db_conn);
	                         row = mysql_fetch_row(rset);
	                         authentication = row[0];
				             if(authentication.compare("0") == 0)		  	 
				             {
                                 stringstream query2;
			  		             query2 << "DELETE FROM playlistRecord where songName = "<<'"' <<songName<<'"'<<"and PID = "
                                   <<'"'<<authentication1<<'"'<<";";
			  		             mysql_free_result(rset);                         
                          		 if((mysql_query(db_conn, query2.str().c_str()))==0)
                          		 {
                                                          cout<<"Song removed from playlist Sucessfully"<<endl;
                                                          flag = true;
                                  }else
                                       {
                                           cout<<mysql_error(db_conn)<<endl;
					                                     }
                             }
				             else
				                 {
					             cout<<"Song does not Exist"<<endl;
					             mysql_free_result(rset);
					             continue;
			                    }
                  }else
		               {	 
                        mysql_free_result(rset);
                       cout<<mysql_error(db_conn)<<endl;
				                     }
			
                 }
                 else
                 {	 mysql_free_result(rset);
                 	cout<<"Playlist Not found"<<endl;
                 	continue;
                 }
       	}else
	{
                cout<<mysql_error(db_conn)<<endl;
        }
      }while(flag == false);
}




