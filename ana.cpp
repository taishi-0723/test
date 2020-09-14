#include <iostream>
#include <cstdlib>
#include <dirent.h>

TString makename(int RUN,TString N){

  TString V = Form("/Users/taishi/work/koto/UCV/%dthrun-UCV/ch0/%s", RUN ,N.Data());

  return V;
}

int f(int RUN){
  int i,j;
  int k=0;
  int x=0;
  int peak1=0;
  int i2,k2,j2,j3,k3,i3;
  double t;
  double val[5000][60];
  double sumMAX=0;
  double peak=0;
  double minpeak=1;
  double noisep=0;
  double noises=0;
  double ineff=0;
  FILE *fp;

 
  TString Q = makename(RUN,"Q.txt");
  TString o = makename(RUN,"offset.txt");
  TString P = makename(RUN,"peak.txt");
  TString A = makename(RUN,"average.txt");
  TString M = makename(RUN,"max_voltage.txt");
  TString N = makename(RUN,"output.txt");
  ofstream ofs(Q);
  ofstream ofs0(o);
  ofstream ofs3(P);
  ofstream ofs4(A);
  ofstream ofs5(M);
  ofstream ofs9(N);
  
  while(k<1000){
    double sum=0;
    double avarage=0;
    double avarage2=0;
    
    //select file
    int K=k;
    string c=to_string(K);
    TString file = Form("/Users/taishi/work/koto/UCV/%dthrun-UCV/ch0/file_%d.dat", RUN, K);
    
    fp=fopen(file,"r");

    if(fp==NULL){
      break;}
  //read file
   for(i=0;i<5000;i++){
   for(j=0;j<51;j++){
     fscanf(fp,"%lf",&val[i][j]);
   }
 }

      //output
   /*  if(k==88 && j==22){
     int J=k;
     string d=to_string(J);
     // string w=to_string(j);
     string e="out"+d+"_14.txt";
     TString X=e;
     TString E=makename(RUN,X);
      ofstream ofs2(E);
      cout << "find" << endl;
 for(i=0;i<2500;i++){
   ofs2 <<val[i][0] << " " << val[i][j] << endl;
 }
 }*/
   
   
 //integral
   for(i=1;i<51;i++){
      for(j=0;j<2500;j++){
	if(j<100){
	  avarage=avarage+val[j][i];
	}
	if(j==100){
	  avarage=avarage/100;
	  t=val[j][0]-val[j-1][0];
	}
	if(val[j][0]>-0.10*pow(10,-6)){
	  
	  sum=sum+(val[j][i]-avarage)/50*t;
	}
	if(j>100){
	  if(val[j][i]-avarage > peak){
	    peak=val[j][i]-avarage;
	    j2=j;
	  }}
      }
      ofs << sum << endl;
      ofs3 << peak << endl;
      ofs5 << val[j2][0] << endl;

      // cout << t << endl;

      if(peak>0.011 && peak<0.013){
	sumMAX++;
	cout << k << " "<< i << endl;
	ofs9 << k << " " << i << endl;
      }
	
      peak=0;
      sum=0;
      j2=0;
      x=0;
      t=0;
      ofs0 << avarage << endl;
      avarage=0;
   }

   k++;
  }
  cout << "inefficiency " << sumMAX << endl; 
 return 0;
}
      
TH1D* photodraw(int RUN){
  
  double MAX=100;
  double min=-10;
  double val;
  double num1=0;
  double num2=0;

  TH1D* hist=new TH1D("name","Charge Distributon; [p.e.];event [#]",200,min,MAX);
  TString Q = makename(RUN,"Q.txt");
  ifstream ifs(Q);

  while(ifs >> val){

    val=val/(1.6e-19*4e6*10);
    hist->Fill(val);

    if(val>MAX){
      num1=num1+1;}
    if(val<min){
      num2=num2+1;}
      
  }

   cout << num1 << " " << num2 << endl;
   
   hist->Draw();

  return hist;
}

TH1D* voltagedraw(int RUN){
  
  double MAX=0.015;
  double min=0;
  double val;

  TH1D* hist=new TH1D("name","Voltage distribution; [V];event [#]",100,min,MAX);

  TString E=makename(RUN,"peak.txt");
  ifstream ifs(E);

  while(ifs >> val){

    hist->Fill(val);
  }

  hist->Draw();

  return hist;

}

TH1D* pedestaldraw(int RUN){
  
  double MAX=-0.01;
  double min=-0.07;
  double val;

  TH1D* hist=new TH1D("name","offset distribution; [V];event [#]",800,min,MAX);

  TString E=makename(RUN,"offset.txt");
  ifstream ifs(E);

  while(ifs >> val){

    hist->Fill(val);
  }

  hist->Draw();

  return hist;
}

TH1D* maxtimedraw(int RUN){
  
  double MAX=0.8*pow(10,-6);;
  double min=-0.4*pow(10,-6);
  double val;

  TH1D* hist=new TH1D("name","max time dstribution; [s];event [#]",200,min,MAX);

  TString E=makename(RUN,"max_voltage.txt");
  ifstream ifs(E);

  while(ifs >> val){

    hist->Fill(val);
  }

  hist->Draw();

  return 0;
}

int fit(TH1D* hist,double min,double max){
  hist->Fit("gaus","","",min,max);

  return 0;
}
