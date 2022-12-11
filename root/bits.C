{

     int n = 7;

     int code = 0;
     bool b[n];

     b[6] = kTRUE;
     b[1] = kFALSE;
     b[2] = kTRUE;


//encode
     for (int i = 0; i < n; i++) {
	  cout << "\t" << i << " -> " << b[i];
	  if (b[i]) code += pow(2, i); 
     }

     cout << endl << code << endl;


//decode
     for (int i = 0; i < n; i++) {
	  bool bit = ((code >> i) & 1);
	  cout << "\t" << i << " -> " << bit;
     }
     
     cout << endl;

     gSystem->Exit(0);








}
