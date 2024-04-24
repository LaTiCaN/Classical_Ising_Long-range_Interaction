BEGIN{
	L = 100
	Nv = 2
	al = 2.0
	T = 0.1
	MCS = 4096
	repeat = 200
	for(i=0;i<40;++i){

		printf("./test	%d  %d  %.4f  %.4f  %d  %d\n",L,Nv,al,T,MCS,repeat);
		T += 0.1;
	}
}

