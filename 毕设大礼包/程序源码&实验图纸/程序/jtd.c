#include <reg51.h>				//ͷ�ļ�
#define uchar unsigned char
#define uint  unsigned int		//�궨��

uchar  buf[4];					//����ʾ�ı���
uchar  sec_EW=20;  			//������Ĭ��
uchar  sec_SN=30;			//�ϱ�Ĭ��ֵ
float  set_EW_time=20;		//���ö��������ʱ��
float  set_SN_time=30;		//�����ϱ������ʱ��
int n;
uchar data countt0,countt1,flag,flag1,flag2,count2,flag3,flag5;//��ʱ��0�жϴ���
//����6�鿪��
sbit  k3=P3^4;		//ȷ��
sbit  k5=P3^1;		//��ֹ
sbit  k6=P1^5;		//ҹ��ģʽ
sbit  k7=P3^7;		  //������⣬ģʽ��
sbit  k8=P3^5;		  //�����������
sbit  k9=P3^6;		//�ϱ��������

sbit BUZZ=P3^0;

sbit Red_SN=P2^6;		//�ϱ���Ʊ�־
sbit Yellow_SN=P2^5;	//�ϱ��ƵƱ�־
sbit Green_SN=P2^4;     //�ϱ��̵Ʊ�־

sbit Red_EW=P2^3;		//������Ʊ�־
sbit Yellow_EW=P2^2;	//�����ƵƱ�־
sbit Green_EW=P2^1;		//�����̵Ʊ�־
		
bit set=0;				//��ʱ�����л�����־ =1ʱ���ϱ���=0ʱ������
bit EW_SN=0;			//�����ϱ�����λ
bit Lighting=0;			//��˸��־λ
bit Night=0;			//ҹ��Ƶ���˸��־λ

uchar code table[11]={	//������������
	0x3f,  //--0
	0x06,  //--1
	0x5b,  //--2
	0x4f,  //--3
	0x66,  //--4
	0x6d,  //--5
	0x7d,  //--6
	0x07,  //--7
	0x7f,  //--8
	0x6f,  //--9
	0x00   //--NULL
};

//��������������
void delay(int ms);			//��ʱ�ӳ���
void key();					//����ɨ���ӳ���
void key_to1();				//�������ӳ���
void key_to2();
void key_to3();
void display();				//��ʾ�ӳ���
void logo();   				//����LOGO
void Buzzer();
//������
void main()
{
	TMOD=0X11;	   				//��ʱ������
	TH1=0X3C;		
	TL1=0XB0;
	TH0=0X3C;					//��ʱ��0�ó�ֵ 0.05S
	TL0=0XB0;
	EA=1;						//�����ж�
	ET0=1;						//��ʱ��0�жϿ���
	ET1=1;					   //��ʱ��1�жϿ���
	TR0=1;						//������ʱ0
	TR1=0;						 	//�رն�ʱ1
	EX0=1;						//���ⲿ�ж�0
	EX1=1;						//���ⲿ�ж�1
    logo();						//������ʼ��
	P2=0Xc3;				// ��ʼĬ��״̬�������̵ƣ��ϱ��Ƶ�   
    sec_SN=sec_EW+5; 			//Ĭ���ϱ�ͨ��ʱ��ȶ�����5��
	while(1)					  //��ѭ��
	{	 
		key(); 					//���ð���ɨ�����
		display(); 				//������ʾ����
	}	
}
//�����Ķ��岿��
	if(k3!=1)							//��K3��ȷ�ϣ�������ʱ
	{	
		display();       				//������ʾ��������ʱ����
		if(k3!=1)						//���ȷ������
		{	flag=0;
			TR0=1;  						//������ʱ��0
			flag3=0;
			TR1=1;
			sec_SN=set_SN_time;				//���жϻظ�������ʾ���ù�����ֵ
			sec_EW=set_EW_time;				//��ʾ���ù���ʱ��
										//�ض�ʱ��1	
			if(set==0)						//ʱ�䵹ʱ��0ʱ
			{ 
				P2=0X00;					 //����ʾ
				Green_EW=1;						//�����̵���
				Red_SN=1;					//�ϱ������
				sec_SN=sec_EW+5; 			//�ص���ֵ
			}
			else 
			{ 
				P2=0x00;					//�ϱ��̵ƣ��������
				Green_SN=1;
				Red_EW=1;
				sec_EW=sec_SN+5; 
			}
		}
	}
	if(k5!=1)							//��K5����ֹ��������ʱ
	{
	   	display();       				//������ʾ��������ʱ����
	   	if(k5!=1)						//���ȷ������
	   	{ 	  flag3=0;
		flag5=1-flag5;
		  if(flag5==1)
	    {	TR0=0;						//�ض�ʱ��
			P2=0x00;					//����ʾ
			Red_EW=1;
			Red_SN=1;			}		//ȫ���ú��  
			if(flag5==0)
{		    TR0=1;
				P2=0X00;					 //����ʾ
				Green_EW=1;						//�����̵���
				Red_SN=1;					//�ϱ������
				sec_EW=set_EW_time;
				sec_SN=sec_EW+5; }		//�ص���ֵ
			do
			{
				display(); 				//������ʾ��������ʱ
			}	
			while(k5!=1);			//�ȴ������ͷ�	
	   	}
	}
	if(k6!=1)							//��K6��ҹ��ģʽ������ 
	{
	   	display();       				//������ʾ��������ʱ���� 
	   	if(k6!=1)						//���ȷ������
	   	{ 	
	    	TR0=0;						//�ض�ʱ��
			P2=0x00;
			flag3=1;
			sec_EW=00;					//�ĸ������ʱ�䶼Ϊ00
			sec_SN=00;
			do
			{
				display(); 			  //������ʾ��������ʱ
			}	
			while(k6!=1);			//�ȴ������ͷ�	
	   	}
	}
	if(k7!=1)							//��K6��ҹ��ģʽ������ 
	{
	   	display();       				//������ʾ��������ʱ���� 
	   	if(k7!=1)						//���ȷ������
	   	{
			flag++;		
			if(flag>=99)					 
			flag=0;		   //ģʽ������Χ����
			if(flag==1)
			{
				TR0=0;TR1=1;
				sec_EW=set_EW_time;
				sec_SN=set_SN_time;	  //��ʾ���õĳ�ʼͨ��ʱ��
				do	
			    { 
					display();       		//������ʾ��������ʱ
				}
				
				while(k7!=1); 
			}
			if(flag==2)
			{
				TR0=0;TR1=1;
				sec_EW=flag2;
				sec_SN=flag1;				  //��ʾ��������
				do	
			    { 
					display();       		//������ʾ��������ʱ
				}
				while(k7!=1); 
			}
	   	}
	}
	if(k8!=1)							// 
	{
	   	display();       				//������ʾ��������ʱ���� 
	   	if(k8!=1)						//���ȷ������
	   	{
			if(Green_EW==1)
			{
				flag2++;  			//������������
				if(flag2>=99)
				flag2=0;	
			}
			else if(Red_EW==1)
			{
				BUZZ=0;
				countt1=0;
			}	      
			
			if(flag==0)
			{
				do	
				{ 
					display();       		//������ʾ��������ʱ
				}
	
				while(k8!=1);
			}
			if(flag==1)
			{
				sec_EW=set_EW_time;
				sec_SN=set_SN_time;				 //��ʾ���õ�ͨ��ʱ��
				do	
				{ 
					display();       		//������ʾ��������ʱ
				}
	
				while(k8!=1);
			}
			if(flag==2)
			{
				sec_SN=flag1;		//��ʾ��������
				sec_EW=flag2;	 
				do	
				{ 
					display();       		//������ʾ��������ʱ
				}
				while(k8!=1);	
			}
		}
	}
	if(k9!=1)							//
	{
	   	display();       				//������ʾ��������ʱ���� 
	   	if(k9!=1)						//���ȷ������
	   	{
			if(Green_SN==1)
			{
				flag1++;				   //�ϱ���������
				if(flag1>=99)
				flag1=0;	
			}
			else if(Red_SN==1)
			{
				BUZZ=0;
				countt1=0;
			}				
								   //����������99
			if(flag==0)
			{
				do	
				{ 
					display();       		//������ʾ��������ʱ
				}
			
				while(k9!=1);
			}
			if(flag==1)
			{
				sec_SN=set_SN_time;		//���õ���ֵ���������ϱ�
				sec_EW=set_EW_time;	 
				do	
				{ 
					display();       		//������ʾ��������ʱ
				}
				while(k9!=1);	
			}
			if(flag==2)
			{
				sec_SN=flag1;		//�����ĳ������������ϱ�
				sec_EW=flag2;	 
				do	
				{ 
					display();       		//������ʾ��������ʱ
				}
				while(k9!=1);	
			}
	   	}
	}
}
void display(void) //��ʾ�ӳ���
{		
	buf[1]=sec_SN/10; 		//��1λ ������ʮλ
	buf[2]=sec_SN%10; 		//��2λ �������λ
	buf[3]=sec_EW/10; 		//��3λ �ϱ���ʮλ
	buf[0]=sec_EW%10; 		//��4λ �ϱ����λ		
	P1=0xff;          		// ��ʼ��Ϊ���
	P0=0x00;				 ////����ʾ
	P1=0xfe;           		//ƬѡLED1
	P0=table[buf[1]];		//�Ͷ���ʱ��ʮλ������ܱ���			
	delay(1);				//��ʱ
	P1=0xff;				//����ʾ
	P0=0x00;				//����ʾ
						   
	P1=0xfd;             	//ƬѡLED2
	P0=table[buf[2]];		 //�Ͷ���ʱ���λ������ܱ���
	delay(1);				 //��ʱ
	P1=0xff;				//����ʾ
	P0=0x00;				//����ʾ
	P1=0Xfb;		  		//ƬѡLED3
	P0=table[buf[3]];		//���ϱ�ʱ��ʮλ������ܱ���
	delay(1);				//��ʱ
	P1=0xff;				 //����ʾ
	P0=0x00;				 //����ʾ
	P1=0Xf7;				 //ƬѡLED4	
	P0=table[buf[0]];		//���ϱ�ʱ���λ������ܱ���
	delay(1);				//��ʱ
}

void time0(void) interrupt 1 using 1  	//��ʱ�ж��ӳ���
{
	TH0=0X3C;							//�ظ���ֵ
	TL0=0XB0;							//12m����50ms//�ظ���ֵ
	TR0=1;								//����������ʱ��
	countt0++;							//���������1
	if(countt0==10)						//�ӵ�10Ҳ���ǰ���
	{
		if((sec_SN<=5)&&(EW_SN==0)&&(Lighting==1))  		//�����Ƶ���		
        {
			Green_EW=0;
			Yellow_EW=0;
		}		   				
	    if((sec_EW<=5)&&(EW_SN==1)&&(Lighting==1))  		//�ϱ��Ƶ���		
        {  
			Green_SN=0;
			Yellow_SN=0;
		}	
	}
		
	if(countt0==20)	                  	// ��ʱ���жϴ���=20ʱ����1��ʱ��
	{	countt0=0;						//���������
		sec_EW--;						//����ʱ���1
		sec_SN--;						//�ϱ�ʱ���1
		
//		BUZZ=1;
		if((sec_SN<=5)&&(EW_SN==0)&&(Lighting==1))  		//�����Ƶ���		
        {
			Green_EW=0;
			Yellow_EW=1;
		}		   				
	    if((sec_EW<=5)&&(EW_SN==1)&&(Lighting==1))  		//�ϱ��Ƶ���		
        {  
			Green_SN=0;
			Yellow_SN=1;
		}		 						
		if(sec_EW==0&&sec_SN==5) 		//����������ʱ��0ʱ������5�룬���ڻƵ���˸ʱ��   
		{
			sec_EW=5;
			Lighting=1;
		}
		if(sec_SN==0&&sec_EW==5)		//���ϱ�����ʱ��0ʱ������5�룬���ڻƵ���˸ʱ��   
		{
			sec_SN=5;
			Lighting=1;
		}
		if(EW_SN==0&&sec_SN==0)			//���Ƶ���˸ʱ�䵹��ʱ��0ʱ��
		{
			P2=0x00;					//���ö����ϱ�����ĺ��̵�
			Green_SN=1;
			Red_EW=1;
			EW_SN=!EW_SN;
			Lighting=0;
																					             
			if(flag1*10/set_SN_time>=5)		   //��������ͨ��ʱ����20�룬��ôͨ���ĳ����ڵ���10������ô�´�ͨ��ʱ���5�룬��Ϊ25��
			{set_SN_time=set_SN_time+5;}		   //��������ͨ��ʱ����25�룬��ôͨ���ĳ����ڵ���12.5��Ҳ���Ǵ��ڵ���13��������ô�´�ͨ��ʱ��ͼ�5�룬��Ϊ30��
			else
			{								   //��������ͨ��ʱ����20�룬��ôͨ���ĳ�С��10������ô�´�ͨ��ʱ���5�룬��Ϊ15��
				set_SN_time=set_SN_time-5;	   //��������ͨ��ʱ����25�룬��ôͨ���ĳ�С��12.5��Ҳ���Ǵ��ڵ���13��������ô�´�ͨ��ʱ��ͼ�5�룬��Ϊ20��
				if(set_SN_time<15)			   //���Ǽ��������޵ļ�����Сͨ��ʱ����15��
				{
					set_SN_time=15;
				}
			}
			flag1=0;			

			sec_SN=set_SN_time;			//�ظ��ϱ��������ʼֵ
			sec_EW=set_SN_time+5;		//�ظ������������ʼֵ
		}		
		if(EW_SN==1&&sec_EW==0)			//���Ƶ���˸ʱ�䵽
		{
			P2=0X00;					//���ö����ϱ��ĺ��̵�״̬
			Green_EW=1;					 //�����̵���
			Red_SN=1;					 //�ϱ������
			EW_SN=!EW_SN;				 //ȡ��
			Lighting=0;					//��˸

			if(flag2*10/set_EW_time>=5)		 //��������ͨ��ʱ����20�룬��ôͨ���ĳ����ڵ���10������ô�´�ͨ��ʱ���5�룬��Ϊ25��
			{set_EW_time=set_EW_time+5;}		 //��������ͨ��ʱ����25�룬��ôͨ���ĳ����ڵ���12.5��Ҳ���Ǵ��ڵ���13��������ô�´�ͨ��ʱ��ͼ�5�룬��Ϊ30��
			else
			{								 //��������ͨ��ʱ����20�룬��ôͨ���ĳ�С��10������ô�´�ͨ��ʱ���5�룬��Ϊ15��
				set_EW_time=set_EW_time-5;	 //��������ͨ��ʱ����25�룬��ôͨ���ĳ�С��12.5��Ҳ���Ǵ��ڵ���13��������ô�´�ͨ��ʱ��ͼ�5�룬��Ϊ20��
				if(set_EW_time<15)			 //���Ǽ��������޵ļ�����Сͨ��ʱ����15��
				{
					set_EW_time=15;
				}
			}
			flag2=0;

			sec_EW=set_EW_time;			//�ظ������������ʼֵ
			sec_SN=set_EW_time+5;		//�ظ��ϱ��������ʼֵ
		}
	}
}
void time1(void) interrupt 3 	//��ʱ�ж��ӳ���
{
	TH1=0X3C;							//�ظ���ֵ
	TL1=0XB0;							//12m����50ms//�ظ���ֵ
	countt1++;							//���������1
	if(countt1==10)					   // ��ʱ���жϴ���=10ʱ����0.5�룩
	{	   
		if(flag3==1)
	    {
			Yellow_SN=0;				//�ϱ��Ƶ���
			Yellow_EW=0;				//�����Ƶ���   
		}	
	}                                                                                                    
	if(countt1==20)	                  	// ��ʱ���жϴ���=20ʱ����1��ʱ��
	{	    
		count2++;
		countt1=0;						//���������
		BUZZ=1;
		if(flag3==1)
		{	
			Yellow_SN=1;					//�ϱ��Ƶ���
			Yellow_EW=1;			 
		} 	//�����Ƶ���
	}
}


//�ⲿ�ж�0
void int0(void) interrupt 0 using 1	   //ֻ������ͨ��
{
	TR0=0;								//�ض�ʱ��0
	TR1=1;flag3=0;								//�ض�ʱ��1
	P2=0x00;							//����ʾ
	Green_EW=1;							//�����������̵�
	Red_SN=1;							//�ϱ�����Ϊ���
	sec_EW=00;							//�ĸ������ʱ�䶼Ϊ00
	sec_SN=00;	
}

//�ⲿ�ж�1
void int1(void) interrupt 2 using 1	  	 //ֻ�����ϱ�ͨ�� 
{
	TR0=0;								//�ض�ʱ��0
	TR1=1;flag3=0;							   //�ض�ʱ��1
	P2=0x00;							//����ʾ
	Green_SN=1;							//���ϱ�����Ϊ�̵�
	Red_EW=1;							//��������Ϊ���
	sec_SN=00;							//�ĸ������ʱ�䶼Ϊ00
	sec_EW=00;
}
void logo()//������Logo  "- - - -"
{ 
	for(n=0;n<50;n++)	//ѭ����ʾ----50��
   	{
	    P0=0x40;  //���Ρ�-��
	    P1=0xfe;	//��һλ��ʾ
		delay(1);	//��ʱ
	    P1=0xfd;	//�ڶ�λ��ʾ
		delay(1);	//��ʱ
		P1=0Xfb;	//����λ��ʾ
		delay(1);	//��ʱ
		P1=0Xf7;	//����λ��ʾ
		delay(1);	//��ʱ
	    P1 = 0xff;	//����ʾ
	}
}

void delay(int ms)		//��ʱ�ӳ���
{
	uint j,k;
	for(j=0;j<ms;j++)			//��ʱms
	   for(k=0;k<124;k++);		//��Լ1�������ʱ
}