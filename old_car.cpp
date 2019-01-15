//area a
cout<<"area A:"<<endl;
		A[0][0].x=2;A[0][0].y=5;
	for(int i=0;i<2;++i){
		A[1][i].x=1-i;A[1][i].y=5;
	}
	for(int i=0;i<2;++i){
		A[1][2+i].x=0;A[1][2+i].y=6+i;
	}
	for(int i=0;i<2;++i){//a2
		A[2][i].x=1;A[2][i].y=6+i;
	}
	for(int i=0;i<2;++i){
		A[2][2+i].x=2+i;A[2][2+i].y=7;
	}
	cout<<A[0][0].x<<" "<<A[0][0].y<<endl;
	for(int i=0;i<4;++i) cout<<A[1][i].x<<" "<<A[1][i].y<<endl;
	for(int i=0;i<4;++i) cout<<A[2][i].x<<" "<<A[2][i].y<<endl;
//area b
	for(int i=0;i<2;++i){
		B[0][i].x=2-i;B[0][i].y=2;
	}
	for(int i=0;i<2;++i){
		B[0][2+i].x=1;B[0][2+i].y=3+i;
	}
	for(int i=0;i<5;++i){
		B[0][4+i].x=0;B[0][4+i].y=4-i;
	}
	for(int i=0;i<2;++i){
		B[0][9+i].x=1;B[0][9+i].y=0+i;
	}
	for(int i=0;i<2;++i){
		B[0][11+i].x=1;B[0][11+i].y=0+i;
	}
	for(int i=0;i<13;++i) cout<<B[0][i].x<<" "<<B[0][i].y<<endl;
//area c
cout<<"area C:"<<endl;
	for(int i=0;i<3;++i){
		C[0][i].x=3;C[0][i].y=2-i;
	}
	for(int i=0;i<3;++i) cout<<C[0][i].x<<" "<<C[0][i].y<<endl;
//area d
cout<<"area D:"<<endl;
	for(int i=0;i<2;++i){
		D[0][i].x=4;D[0][i].y=2-i;
	}
	for(int i=0;i<2;++i) cout<<D[0][i].x<<" "<<D[0][i].y<<endl;
//area e
cout<<"area E:"<<endl;
	for(int i=0;i<2;++i){
		E[0][i].x=5+i;E[0][i].y=2;
	}
	for(int i=0;i<3;++i){
		E[1][i].x=7;E[1][i].y=2+i;
	}
	for(int i=0;i<2;++i){
		E[2][i].x=7;E[2][i].y=1-i;
	}
	for(int i=0;i<2;++i){
		E[3][i].x=6;E[3][i].y=1-i;
	}
	for(int i=0;i<2;++i){
		E[4][i].x=5;E[4][i].y=1-i;
	}
		E[4][2].x=4;E[4][2].y=0;
	for(int i=0;i<2;++i) cout<<E[0][i].x<<" "<<E[0][i].y<<endl;
	for(int i=0;i<3;++i) cout<<E[1][i].x<<" "<<E[1][i].y<<endl;
	for(int i=0;i<2;++i) cout<<E[2][i].x<<" "<<E[2][i].y<<endl;
	for(int i=0;i<2;++i) cout<<E[3][i].x<<" "<<E[3][i].y<<endl;
	for(int i=0;i<3;++i) cout<<E[4][i].x<<" "<<E[4][i].y<<endl;
//area F
cout<<"area F:"<<endl;
	for(int i=0;i<2;++i){
		F[0][i].x=5;F[0][i].y=3-i;
	}
	for(int i=0;i<2;++i) cout<<F[0][i].x<<" "<<F[0][i].y<<endl;
//area G
cout<<"area G:"<<endl;
	G[0][0].x=5;G[0][0].y=5;
	for(int i=0;i<2;++i){
		G[1][i].x=6+i;G[1][i].y=5;
	}
	for(int i=0;i<2;++i){
		G[2][i].x=6;G[2][i].y=4-i;
	}
	cout<<G[0][0].x<<" "<<G[0][0].y<<endl;
	for(int i=0;i<2;++i) cout<<G[1][i].x<<" "<<G[1][i].y<<endl;
	for(int i=0;i<2;++i) cout<<G[2][i].x<<" "<<G[2][i].y<<endl;
//area h
cout<<"area H:"<<endl;
		H[0][0].x=4;H[0][0].y=5;
	for(int i=0;i<2;++i){
		H[0][1+i].x=4+i;H[0][1+i].y=6;
	}
		H[1][0].x=6;H[1][0].y=6;
	for(int i=0;i<2;++i){
		H[1][1+i].x=7;H[1][1+i].y=6+i;
	}
	for(int i=0;i<3;++i){//h2
		H[2][i].x=6-i;H[2][i].y=7;
	}
	for(int i=0;i<3;++i) cout<<H[1][i].x<<" "<<H[1][i].y<<endl;
	for(int i=0;i<3;++i) cout<<H[1][i].x<<" "<<H[1][i].y<<endl;
	for(int i=0;i<3;++i) cout<<H[2][i].x<<" "<<H[2][i].y<<endl;
//area I
cout<<"area I:"<<endl;
	for(int i=0;i<2;++i){
		I[0][i].x=3;I[0][i].y=5-i;
	}
	for(int i=0;i<2;++i){
		I[1][i].x=3-i;I[1][i].y=6;
	}
	for(int i=0;i<2;++i) cout<<I[0][i].x<<" "<<I[0][i].y<<endl;
	for(int i=0;i<2;++i) cout<<I[1][i].x<<" "<<I[1][i].y<<endl;
