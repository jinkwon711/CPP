  // for(int i=1; i<argc;i++){
  //   ifstream inFile(argv[i]);
  //   while(!inFile.eof()){
  //     getline(inFile,line);//getline
  //     string tempString="";
  //     for(int i=0; i!=line.length(); i++){
  //       if(line[i]==','||line[i]=='\0'){
  //         item.push_back(tempString);
  //         tempString="";
  //       }
  //       else tempString+=line[i];//split by ','
  //     }
  //     item.push_back(tempString);
  //     csvItem.push_back(item);
  //     item.clear();
  //     // temp = &csvItem;
  //   }
  //   totalCsvItem.push_back(csvItem);
  //   csvItem.clear();
  // }
  //below , used for the input checking
  // for(int i=0; i!=totalCsvItem.size();i++){
  //   for(auto it:totalCsvItem[i]){
  //     for(auto it2:it){
  //       cout<<it2;
  //     }
  //     cout<<endl;
  //   }
  // }
cvs 인풋 체크 코드
for(auto &cvsObj:cvs_vec){
  for(auto &it:*cvsObj->field[0]){
      cout<<it<<"  ";
    }
    cout<<endl;
  for(auto &it:*cvsObj->type[0]){
      cout<<it<<"  ";
    }
    cout<<endl;
  
  for(auto &item:cvsObj->data){
    for(auto &it:*item){
        cout<<it<<"  ";
    }
    cout<<endl;
  }
}