#include "iostream"
#include "gl/glut.h"
#include "string"
#include "vector"
#include "set"
#include "stdio.h"
#include "math.h"
#include "algorithm"
#include "fstream"

#define WIDTH_RIGHT 300 //�����ұ߽�
#define WIDTH_LEFT -300	//������߽�
#define HEIGHT_TOP 300	//�����ϱ߽�
#define HEIGHT_BOTTOM -300 //�����±߽�
#define MAGNIFICATION 20//�Ŵ���
#define PI 3.14159265 
using namespace std;

void Display1();
void Display2();
void Draw(int argc,char *argv[]);
void Matrix_mul(vector<vector<double>> &vertex1,vector<vector<double>> &vertex2,vector<vector<double>> &vertex);
void Revolve();
void Symmetric();
void Shear();
void BasicTransformation();
void Complex_Revolve();
void Complex_Symmetric_Line();
void Complex_Symmetric_Point();
void Complex_Symmetric();
void ComplexTransformation();

vector<vector<double>> T(4,vector<double>(4,0));//���ı任����
vector<vector<double>> Tnew(4,vector<double>(4,0));//������һ������Ҫ�õ��ı任����
vector<vector<double>> Ttmp(4,vector<double>(4,0));//��ʱ�任���������������˵Ľ��
vector<vector<double>> GraphPoint;
vector<vector<int>> IndexPoint;//��Ҫ���л��Ƶ�����б�ţ����ڻ���
int arr[3]; //arr[0] ��ʾ�˵����� arr[1]��ʾ��Ƭ����

/*
������˺���
����:ʵ�־����������
���������vertex1:����� vertex2 �Ҿ��� vertex �������
*/
void Matrix_mul(vector<vector<double>> &vertex1,vector<vector<double>> &vertex2,vector<vector<double>> &vertex){
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++){
			vertex[i][j]=0;
		}
	}
	int n=vertex1.size();
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<4;k++)
			{
				vertex[i][j]+=vertex1[i][k]*vertex2[k][j];
			}
		}
	}

	/*for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++){
			cout<<vertex[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;*/
}


/*
���Ʊ任ǰͼ�κ���
���ܣ�����OpenGL���Ʊ任ǰ��ͼ��
*/
void Display1()
{   

	//gluOrtho2D(WIDTH_LEFT,WIDTH_RIGHT,HEIGHT_BOTTOM,HEIGHT_TOP);//���ƻ�ͼȡֵ��Χ
	//glTranslatef(WIDTH_LEFT+100,HEIGHT_BOTTOM+100,0);
	/*
	vector<vector<double>> axis(4,vector<double>(4,0));
	for(int i=0;i<2;i++)
	{
		axis[2*i][i]=-1;axis[2*i][3]=1;
		axis[2*i+1][i]=1;axis[2*i+1][3]=1;
	}
	//vector<vector<double>> axisTrs(6,vector<double>(4,0));
	//Matrix_mul(axis,DisT,axisTrs);
	*/
	
	double disT[4][4]={
		1,0,0,0,
		0,1,0,0,
		0.5*cos(45*PI/180),0.5*sin(45*PI/180),0,0,
		0,0,0,1,
	};
	vector<vector<double>> DisT;//б��ͶӰת������
	for(int i=0;i<4;i++){
		vector<double> temp(disT[i],disT[i]+4);
		DisT.push_back(temp);
	}
	vector<vector<double>> Vertex(GraphPoint.size(),vector<double>(4,0));
	Matrix_mul(GraphPoint,DisT,Vertex);//б��ͶӰת��
	GraphPoint=Vertex;
	
	glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_TRIANGLES);
	for (int i = 0; i <arr[1]; i++)
    {
		int size=IndexPoint[i].size();
        for (int j = 0; j <size; j++) {
			glVertex3f(GraphPoint[IndexPoint[i][j]][0],GraphPoint[IndexPoint[i][j]][1],GraphPoint[IndexPoint[i][j]][2]);
        }
    }
	glEnd();
	glFlush();
}
/*
���Ʊ任��ͼ�κ���
���ܣ�����OpenGL���Ʊ任���ͼ��
*/
void Display2()
{   

	//gluOrtho2D(WIDTH_LEFT,WIDTH_RIGHT,HEIGHT_BOTTOM,HEIGHT_TOP);//���ƻ�ͼȡֵ��Χ
	//glTranslatef(WIDTH_LEFT+100,HEIGHT_BOTTOM+100,0);
	
	
	
	vector<vector<double>> VertexTrs(GraphPoint.size(),vector<double>(4,0));
	Matrix_mul(GraphPoint,T,VertexTrs);
	

	double disT[4][4]={
		1,0,0,0,
		0,1,0,0,
		0.5*cos(45*PI/180),0.5*sin(45*PI/180),0,0,
		0,0,0,1,
	};
	vector<vector<double>> DisT;
	for(int i=0;i<4;i++){
		vector<double> temp(disT[i],disT[i]+4);
		DisT.push_back(temp);
	}
	vector<vector<double>> Vertex(GraphPoint.size(),vector<double>(4,0));
	Matrix_mul(VertexTrs,DisT,Vertex);//б��ͶӰת��
	VertexTrs=Vertex;
	
	glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_TRIANGLES);
	for (int i = 0; i <arr[1]; i++)
    {
		int size=IndexPoint[i].size();
        for (int j = 0; j <size; j++) {
			glVertex3f(VertexTrs[IndexPoint[i][j]][0],VertexTrs[IndexPoint[i][j]][1],VertexTrs[IndexPoint[i][j]][2]);
        }
    }
	glEnd();
	glFlush();
}

/*
չʾ���ں���
���ܣ������Ƶ�ͼ��չʾ
*/
void Draw(int argc,char *argv[])
{
	
	glutInit(&argc,argv);    //��ʼ��glut,������ã����������仰����  
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //������ʾ��ʽ��RGB�������塣��Ȼ����GLUT_INDEX������ɫ GLUT_DOUBLE˫����(Qt�п�����˫����)  
    glutInitWindowPosition(50,100);   //λ��  
	glutInitWindowSize(WIDTH_RIGHT-WIDTH_LEFT,HEIGHT_TOP-HEIGHT_BOTTOM);//���ڴ�С  
    glutCreateWindow("3D_graphics_conversion1");  //�������ڣ����ñ���  
	
	glutDisplayFunc(&Display1);  // �����ƴ���ʱ����myDisplay����Cocos2d-xˢ֡Draw�еĲ���  
	//glutIdleFunc(&renderScene);
	glutInitWindowPosition(650,100);   //λ��  
	glutCreateWindow("3D_graphics_conversion2");  //�������ڣ����ñ���  
	
	glutDisplayFunc(&Display2);  // �����ƴ���ʱ����myDisplay����Cocos2d-xˢ֡Draw�еĲ���  

    glutMainLoop();  //��Ϣѭ�� 
}
/*
�����任-��ת���溯��
���ܣ���ͼ�ν�����ת
*/
void Revolve()
{
	cout<<"*------------------------------------*"<<endl;
	cout<<"          1.��x����ת                      "<<endl;
	cout<<"          2.��y����ת                   "<<endl;
	cout<<"          3.��z����ת                      "<<endl;
	cout<<"��ѡ��";int choose; cin>>choose;
	cout<<"���밴��ʱ�뷽����ת�Ƕ�[0--360]���㣩��";double p;
	cin>>p;
	double Cos=cos(p*PI/180),Sin=sin(p*PI/180);
	switch (choose)
	{
	case 1:
		T[0][0]=Cos;T[0][1]=Sin;T[1][0]=-Sin;T[1][1]=Cos;break;
	case 2:
		T[0][0]=Cos;T[0][2]=-Sin;T[2][0]=Sin;T[2][2]=Cos;break;
	case 3:
		T[1][1]=Cos;T[1][2]=Sin;T[2][1]=-Sin;T[2][2]=Cos;break;
	default:
		break;
	}
}

/*
�����任-�Գƽ��溯��
���ܣ���ͼ�ν��жԳƱ任
*/
void Symmetric()
{
	cout<<"*------------------------------------*"<<endl;
	cout<<"          1.XOYƽ��Գ�                      "<<endl;
	cout<<"          2.YOZƽ��Գ�                   "<<endl;
	cout<<"          3.XOZƽ��Գ�                      "<<endl;
	cout<<"          4.X��Գ�                      "<<endl;
	cout<<"          5.Y��Գ�               "<<endl;
	cout<<"          6.Z��Գ�                      "<<endl;
	cout<<"��ѡ��";
	int k;
	cin>>k;
	switch (k)
	{
	case 1:T[2][2]=-1;break;
	case 2:T[0][0]=-1;break;
	case 3:T[1][1]=-1;break;
	case 4:T[1][1]=-1;T[2][2]=-1;break;
	case 5:T[0][0]=-1;T[2][2]=-1;break;
	case 6:T[0][0]=-1;T[1][1]=-1;break;
	default:
		break;
	}
}
/*
�����任-���н��溯��
���ܣ���ͼ�ν��д��б任
*/
void Shear()
{
	cout<<"*------------------------------------*"<<endl;
	cout<<"          1.��x�᷽�����                      "<<endl;
	cout<<"          2.��y�᷽�����                   "<<endl;
	cout<<"          3.��z�᷽�����                      "<<endl;
	cout<<"��ѡ��";
	int k;
	cin>>k;
	double a,b;
	cout<<"�������ϵ��:";
	cin>>a>>b;
	switch (k)
	{
	case 1:
		Tnew[1][0]=a;Tnew[2][0]=b;break;
	case 2:
		Tnew[0][1]=a;Tnew[2][1]=b;break;
	case 3:
		Tnew[0][2]=a;Tnew[1][2]=b;break;
	default:
		break;
	}
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
}
/*
�������α任���溯��
���ܣ�ѡ��Ҫ���еı任����
*/
void BasicTransformation()
{
	cout<<"*--------�������α任----------------*"<<endl;
	cout<<"          1.ƽ��                      "<<endl;
	cout<<"          2.��ת                   "<<endl;
	cout<<"          3.����                      "<<endl;
	cout<<"          4.�Գ�                   "<<endl;
	cout<<"          5.����                   "<<endl;
	cout<<"��ѡ��";
	int k;
	cin>>k;
	double x,y,z;
	switch (k)
	{
	case 1:
		cout<<"x�᷽��ƽ�ƾ��� y�᷽��ƽ�ƾ��� z�᷽��ƽ�ƾ���:" ;cin>>x>>y>>z;
		T[3][0]=x;T[3][1]=y;T[3][2]=z;T[3][3]=1;
		break;
	case 2:
		Revolve();	break;
	case 3:
		cout<<"x�᷽�����ű��� y�᷽�����ű��� z�᷽�����ű���:" ;cin>>x>>y>>z;
		T[0][0]=x;T[1][1]=y;T[2][2]=z;
		break;
	case 4:
		Symmetric();
		break;
	case 5:
		Shear();break;
	default:
		break;
	}
}
/*
���ϱ任-��ֱ����ת���溯��
���ܣ�������ת���Լ���ת�Ƕȣ�������ת
*/
void Complex_Revolve()
{
	cout<<"��������ֱ����ת��ֱ�����˵�ֵ(x1,y1,z1) , (x2,y2,z2)��";
	double x1,y1,z1,x2,y2,z2;
	cin>>x1>>y1>>z1>>x2>>y2>>z2;
	cout<<"����������ʱ����ת�Ƕ�[0--360]���㣩��";
	double p;
	cin>>p;
	double Sinp=sin(p*PI/180),Cosp=cos(p*PI/180);

	bool flag1=false;
	if(x1==0&&y1==0&&z1==0){}
	else{
		//����ƽ�Ʊ任
		flag1=true;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++){
				Tnew[i][j]=0;
			}
			Tnew[i][i]=1;
		}
		Tnew[3][0]=-x1,Tnew[3][1]=-y1,Tnew[3][2]=-z1;
		Matrix_mul(T,Tnew,Ttmp);
		T=Ttmp;
	}
	double v_x=x2-x1,v_y=y2-y1,v_z=z2-z1;//�߶ε�������ʾ
	double ABlen=sqrt(pow(v_x,2)+pow(v_y,2)+pow(v_z,2));//�߶εĳ���
	double BB_=v_x;//B��������YOZƽ��Ĵ���B'��x���� ����
	double AB_len=sqrt(pow(v_z,2)+pow(v_y,2));//A���봹��B'�ĳ���
	double Sina=v_y/AB_len,Cosa=v_z/AB_len;
	if(AB_len==0){//�����ж�
		Sina=0;Cosa=1;
	}
	double Sinb=BB_/ABlen,Cosb=AB_len/ABlen;
	//cout<<ABlen<<" "<<BB_<<" "<<AB_len<<" "<<Sina<<" "<<Cosa<<" "<<Sinb<<" "<<Cosb<<endl<<endl;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++){
			Tnew[i][j]=0;
		}
		Tnew[i][i]=1;
	}
	//����ת����ת��XOZƽ��
	Tnew[1][1]=Cosa;Tnew[1][2]=Sina;Tnew[2][1]=-Sina;Tnew[2][2]=Cosa;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[1][1]=1;Tnew[1][2]=0;Tnew[2][1]=0;Tnew[2][2]=1;
	//����ת����ת����Z���غ�
	Tnew[0][0]=Cosb;Tnew[0][2]=Sinb;Tnew[2][0]=-Sinb;Tnew[2][2]=Cosb;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[0][0]=1;Tnew[0][2]=0;Tnew[2][0]=0;Tnew[2][2]=1;
	//�������õ���ת�任
	Tnew[0][0]=Cosp;Tnew[0][1]=Sinp;Tnew[1][0]=-Sinp;Tnew[1][1]=Cosp;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[0][0]=1;Tnew[1][1]=1;Tnew[0][1]=0;Tnew[1][0]=0;
	//����ת����ת����Z���غϵ���任
	Tnew[0][0]=Cosb;Tnew[0][2]=-Sinb;Tnew[2][0]=Sinb;Tnew[2][2]=Cosb;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[0][0]=1;Tnew[0][2]=0;Tnew[2][0]=0;Tnew[2][2]=1;
	//����ת����ת��XOZƽ�����任
	Tnew[1][1]=Cosa;Tnew[1][2]=-Sina;Tnew[2][1]=Sina;Tnew[2][2]=Cosa;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[1][1]=1;Tnew[1][2]=0;Tnew[2][1]=0;Tnew[2][2]=1;
	//���������ƽ�Ʊ任���Ҫ����ƽ�Ʊ任����任
	if(flag1)
	{
		Tnew[3][0]=x1,Tnew[3][1]=y1,Tnew[3][2]=z1;
		Matrix_mul(T,Tnew,Ttmp);
		T=Ttmp;
	}
}
/*
���ϱ任-����ֱ�߶Գƽ��溯��
���ܣ����öԳ��ᣬ�ҵ����ĶԳƱ任����
*/
void Complex_Symmetric_Line()
{
	cout<<"���������ĳֱ�߶ԳƵ�ֱ�����˵�ֵ(x1,y1,z1) , (x2,y2,z2)��";
	double x1,y1,z1,x2,y2,z2;
	cin>>x1>>y1>>z1>>x2>>y2>>z2;
	bool flag1=false;
	if(x1==0&&y1==0&&z1==0){}
	else{
		flag1=true;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++){
				Tnew[i][j]=0;
			}
			Tnew[i][i]=1;
		}
		Tnew[3][0]=-x1,Tnew[3][1]=-y1,Tnew[3][2]=-z1;
		Matrix_mul(T,Tnew,Ttmp);
		T=Ttmp;
	}
	double v_x=x2-x1,v_y=y2-y1,v_z=z2-z1;
	double ABlen=sqrt(pow(v_x,2)+pow(v_y,2)+pow(v_z,2));
	double BB_=v_x;
	double AB_len=sqrt(pow(v_z,2)+pow(v_y,2));
	double Sina=v_y/AB_len,Cosa=v_z/AB_len;
	if(AB_len==0){
		Sina=0;Cosa=1;
	}
	double Sinb=BB_/ABlen,Cosb=AB_len/ABlen;
	cout<<ABlen<<" "<<BB_<<" "<<AB_len<<" "<<Sina<<" "<<Cosa<<" "<<Sinb<<" "<<Cosb<<endl<<endl;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++){
			Tnew[i][j]=0;
		}
		Tnew[i][i]=1;
	}
	Tnew[1][1]=Cosa;Tnew[1][2]=Sina;Tnew[2][1]=-Sina;Tnew[2][2]=Cosa;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[1][1]=1;Tnew[1][2]=0;Tnew[2][1]=0;Tnew[2][2]=1;

	Tnew[0][0]=Cosb;Tnew[0][2]=Sinb;Tnew[2][0]=-Sinb;Tnew[2][2]=Cosb;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[0][0]=1;Tnew[0][2]=0;Tnew[2][0]=0;Tnew[2][2]=1;

	Tnew[0][0]=-1;Tnew[1][1]=-1;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[0][0]=1;Tnew[1][1]=1;

	Tnew[0][0]=Cosb;Tnew[0][2]=-Sinb;Tnew[2][0]=Sinb;Tnew[2][2]=Cosb;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[0][0]=1;Tnew[0][2]=0;Tnew[2][0]=0;Tnew[2][2]=1;

	Tnew[1][1]=Cosa;Tnew[1][2]=-Sina;Tnew[2][1]=Sina;Tnew[2][2]=Cosa;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[1][1]=1;Tnew[1][2]=0;Tnew[2][1]=0;Tnew[2][2]=1;

	if(flag1)
	{
		Tnew[3][0]=x1,Tnew[3][1]=y1,Tnew[3][2]=z1;
		Matrix_mul(T,Tnew,Ttmp);
		T=Ttmp;
	}
}
/*
���ϱ任-����һ��Գƽ��溯��
���ܣ����öԳƵ㣬����ԳƱ任����
*/
void Complex_Symmetric_Point()
{
	cout<<"������ĳ�˵�ֵ(x1,y1,z1)��";
	double x1,y1,z1;
	cin>>x1>>y1>>z1;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++){
			Tnew[i][j]=0;
		}
		Tnew[i][i]=1;
	}
	Tnew[3][0]=-x1,Tnew[3][1]=-y1,Tnew[3][2]=-z1;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[3][0]=0,Tnew[3][1]=0,Tnew[3][2]=0;

	Tnew[0][0]=-1,Tnew[1][1]=-1,Tnew[2][2]=-1;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[0][0]=1,Tnew[1][1]=1,Tnew[2][2]=1;

	Tnew[3][0]=x1,Tnew[3][1]=y1,Tnew[3][2]=z1;
	Matrix_mul(T,Tnew,Ttmp);
	T=Ttmp;
	Tnew[3][0]=0,Tnew[3][1]=0,Tnew[3][2]=0;
}
/*
���ϱ任-�Գƽ��溯��
���ܣ�ѡ�����ֱ�߶Գƻ��ǹ��ڵ�Գ�
*/
void Complex_Symmetric()
{
	cout<<"*------------------------------------*"<<endl;
	cout<<"          1.����ĳֱ�߶Գ�                      "<<endl;
	cout<<"          2.����ĳ��Գ�                   "<<endl;
	cout<<"��ѡ��";
	int k;
	cin>>k;
	switch (k)
	{
	case 1:
		Complex_Symmetric_Line();break;
	case 2:
		Complex_Symmetric_Point();break;
	default:
		break;
	}
}
/*
���ϱ任���溯��
���ܣ�ѡ��Ҫ���еı任����
*/
void ComplexTransformation()
{
	while(true)
	{
		cout<<"*--------���ϱ任--------------------*"<<endl;
		cout<<"          1.ƽ��                      "<<endl;
		cout<<"          2.��ת                   "<<endl;
		cout<<"          3.����                   "<<endl;
		cout<<"          4.�Գ�                   "<<endl;
		cout<<"          5.����                   "<<endl;
		cout<<"          6.       ���                   "<<endl;
		cout<<"��ѡ��";
		int k;
		cin>>k;
		double x,y,z;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++){
				Tnew[i][j]=0;
				Ttmp[i][j]=0;
			}
			Tnew[i][i]=1;
		}
		switch (k)
		{
		case 1:
			cout<<"x�᷽��ƽ�ƾ��� y�᷽��ƽ�ƾ��� z�᷽��ƽ�ƾ���:" ;cin>>x>>y>>z;
			Tnew[3][0]=x;Tnew[3][1]=y;Tnew[3][2]=z;
			Matrix_mul(T,Tnew,Ttmp);
			T=Ttmp;
			break;
		case 2:

			Complex_Revolve();	break;
		case 3:
			cout<<"x�᷽�����ű��� y�᷽�����ű��� z�᷽�����ű���:" ;cin>>x>>y>>z;
			Tnew[0][0]=x;Tnew[1][1]=y;Tnew[2][2]=z;
			Matrix_mul(T,Tnew,Ttmp);
			T=Ttmp;
			break;
		case 4:
			Complex_Symmetric();
			break;
		case 5:
			Shear();break;
		default:
			return ;
		}
		
	}
}
/*
��ʼ������
���ܣ��ļ����ݽ��ж���
*/
void Init()
{
	ifstream infile;
	infile.open("ģ��/2.off");
	string s;
	double t;
	infile >> s;
	
	for(int i=0;i<3;i++)
	{
			infile >> arr[i];
	}
	GraphPoint=vector<vector<double>>(arr[0],vector<double>(4,1));
	IndexPoint=vector<vector<int>>(arr[1]);
	int cnt = 0;
	for (int i=0;i<arr[0];i++)
	{
		for (int j=0;j<3;j++)
			infile >> GraphPoint[i][j];
	}
	int size,temp;
	for(int i=0;i<arr[1];i++)
	{
		infile>>size;
		for(int j=0;j<size;j++)
		{
			infile>>temp;
			IndexPoint[i].emplace_back(temp);
		}
	}
	infile.close();//��ȡ���֮��ر��ļ�
}
/*
������
*/
int main(int argc, char* argv[])
{
	Init();
	for(int i=0;i<4;i++){
		T[i][i]=1;
	}
	cout<<"*------------------------------------*"<<endl;
	cout<<"          1.�������α任              "<<endl;
	cout<<"          2.  ���ϱ任                "<<endl;
	cout<<"��ѡ��";
	int x;
	cin>>x;
	switch (x)
	{
	case 1:BasicTransformation();break;
	case 2:ComplexTransformation();break;
	default:
		return 0;
	}
	Draw(argc,argv);
}























/*
float rotates = 0;
int times = 0;
void renderScene() 
{
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    glPushMatrix();

    //glTranslatef(-0.2, 0, 0); // ƽ��

    //glScalef(2, 1, 1);    // ����

    times++;
    if(times > 100)
    {
        times = 0;
    }

    if(times % 100 == 0)
    {
        rotates += 0.3;
    }
    
    glRotatef(rotates, 0, 1, 0);
    glRotatef(rotates, 1, 0, 0);

    

	Display1();

    glPopMatrix();
    glutSwapBuffers();
}
*/
