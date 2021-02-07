#include "Utilitarios.h"

vector<string> split(string str,string regex){
	vector<string> result = vector<string>();
	int init_Pos = 0, index = str.find(regex);

	while(index != int(string::npos)){
		result.push_back(str.substr(init_Pos,index - init_Pos));
		init_Pos = index+regex.size();
		index = str.find(regex,init_Pos);
	}

	result.push_back(str.substr(init_Pos,index-init_Pos));

	return result;
}
