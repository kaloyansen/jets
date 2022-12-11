{
     double x, min = kMinLong, max = kMaxLong, pi = 22 / 7.;

     TDatime datime;
     TRandom random(datime.Get());

     bool loop = kTRUE;
     while (loop) {
	  x = random.Uniform(min, max);
	  if (x > pi) max = x;
	  if (x < pi) min = x;
	  cout << x - pi << " ";
	  if (x == pi) loop = kFALSE;
     }
     cout << endl;
}
