main() {
  int i;
  int b = 4 + 3;

  double dd = 2.3;

  bool d;
  bool z = true;

  String xixi;
  String s = "Hello World";

  print(s);
  print(b);
  print(z);
  print(4 * b);

  print("Teste1 if-else");
  if(true){
	print("If-else funcionando");
  }else{
  	print("If-else não está funcionando");
  }

  print("Teste2 if-else");
  if(false){
  	print("If-else não está funcionando");
  }else{
    print("If-else funcionando");
  }

  print("Teste if");
  if(z){
  	print("If está funcionando");
  }

  i = 1 + 2 - 20 / 4 * 5;

  print(i);

  bool j = true;

  i = 10;

  if(i < 5){
    	print("If i > 5 funcionando também!");
  }

  print("Teste While");

  while(i > 5){
  	i = i - 1;

  	if(i == 5){
  		j = false;
  		print(j);
  	}

  	print(i);
  }
}