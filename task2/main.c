#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���ҽ��i�ĸ����,ͨ���ݹ�õ���㵽���ĳ���
int findParent(int i,int huffman[][4],int n);
//���ݳ�ʼȨ�ع�����������
void huffmanTree(int w[],int huffman[][4],int n);
//Ѱ��Ȩ����С�������ڵ�
void findMin(int ii[],int huffman[][4],int n);
//��ÿ��Ҷ�ڵ���й���������
void HuffmanCode(int i,int huffman[][4],int n);
//��������char������
void inplace_swap(char *x,char *y);

int main()
{
    //��������ַ������м�¼�����ַ����ܸ���count�Լ������ַ��ĳ��ִ���arr_small[]����ͳ��
    char str[100];
    printf("Please Enter the string\n");
    scanf("%s", str);
    int arr_big[27] = {0};  //�����ַ��ĳ��ִ���
    int count = 0;  //�ַ����ܸ���
    for(int i = 0; i < strlen(str); i++)    //���������ַ����е������ַ�
    {
        for(int j = 0; j < 27; j++) //����26����д��ĸ
        {
            if(str[i] == (char)(0x41+ j))
            {
                arr_big[j] += 1;
                if(arr_big[j] == 1)
                {
                    count += 1;		//��¼һ�������˼�����ĸ
                }
                break;
            }
        }
    }
    printf("the letter count is %d\n",count);   //��ӡ�����ַ��������˼�����ĸ

    //ͨ��arr_big�������ַ����г��ֵ���ĸ��������ͳ�ƣ���������arr_small��
    int count2 = 0;     //�ַ����г��ֵ��ַ��ܸ���
    int arr_small[count] ;  //ͳ�������ַ�������ĸ�ĳ��ִ���
    for(int i = 0; i < 27; i++)
    {
        if(arr_big[i]!=0)
        {
            arr_small[count2++] = arr_big[i];	// ��arr_big�����еķ���ֵͬ��������arr_small�У��ж��ٸ����ݶ�Ӧ�ж��ٸ���ĸ����   
        }
    }
    //����int�Ͷ�ά���飬���鳤��[*]Ϊ���������Ľڵ����
    //c[*][0]��ŵ��Ǹýڵ��[���ڵ��λ��]��c[*][1]Ϊ�ýڵ��[�������ڵ��λ��]
    //c[*][2]��Ÿýڵ��[�������ڵ��λ��]��c[*][3]Ϊ�ýڵ��Ȩֵ
    int huffman[2 * count - 1][4];  //ǰn��ΪҶ��㣬��n-1��Ϊ�м���

    //���ݳ�ʼȨ������arr_small���ַ���������huffman��
    huffmanTree(arr_small,huffman,count);

    //����Huffman���������ܳ���WPL
    int sum = 0;
    for(int i = 0;i < count;i++)
    {
        int length = 0;
        if(huffman[i][1] == -1 && huffman[i][2] == -1)  /*�жϸý���Ƿ��û��������û���ҽ�㣬���Ƿ�ΪҶ���*/
        {
            length = findParent(i,huffman,count);   //�õ�����Ҷ���Ĵ�Ȩ·������
            sum += length * huffman[i][3];                    //����Ҷ����Ȩ·�������ۼӵõ��ܳ���WPL
        }
    }
   
    printf("the tree's WPL  is  %d\n",sum);

    //Huffman����
    for(int i = 0;i < count;i++)
    {
        HuffmanCode(i,huffman,count);
    }

    return 0;
}

//�Ӻ�������������������
void huffmanTree(int w[],int huffman[][4],int n)
{
    //����ʼ��
    for(int i = 0; i < 2 * n - 1; i++)
    {
        huffman[i][0] = -1;
        huffman[i][1] = -1;
        huffman[i][2] = -1;
        huffman[i][3] = -1;
    }
    /*��Ҷ�ڵ��Ȩ����ӵ���ά������*/
    for(int i = 0; i < n; i++)
    {
        huffman[i][3] = w[i];
    }
    //ÿ�γ������Ȩ����С�Ľ����кϲ���ֱ�����ղ��������
    for(int i = n; i < 2 * n - 1; i++)
    {
        int i1,i2;  //Ȩ����С���������
        int ii[2];   
        //�ҳ�����Ȩ����С�Ľ��
        findMin(ii, huffman, n);
        i1=ii[0];
        i2=ii[1];
        //�ϲ�i1��i2���,���½����Ϣ�������ɽ��������ӽ�㣬�ӽڵ��Ӧ�ĸ���㣬�����ɽ���Ȩ�أ�
    
        huffman[i][1] = i1;         //���ӽ�� 
        huffman[i][2] = 12;         //���ӽ�� 
        huffman[i][3] = huffman[i1][3] + huffman[i2][3];             //Ȩ��
        huffman[i1][0] = huffman[i2][0] = i;                         //�ӽڵ��Ӧ�ĸ��ڵ�

    }
}

//�Ӻ��������ҳ�����Ȩ����С�Ľ��
void findMin(int ii[],int huffman[][4],int n)
{
    //�ҳ���һ��Ȩ����С�Ľ��
    int min1= 9999999;
    
    for(int i = 0; i < 2 * n - 1; i++)
    {
        if(huffman[i][3] == -1 && huffman[i][0] == -1)  /*�ų���δͨ���ϲ��ӽڵ����¸�ֵ�Ľ��*/
        {
            break;
        }
        if(huffman[i][3] < min1 && huffman[i][0] == -1)  /*���ж����Ƿ�С��min���ٸ�����û�и�������ж����ǿ��Ժϲ����ӽ�㣬������ͬʱ����*/
        {                                                
            min1= huffman[i][3];                              
            ii[0] = i;
          
        }

    }
    int min2= 9999999;
    for (int j = 0; j < 2 * n - 1; j++)
    {
        if (huffman[j][3] == -1 && huffman[j][0] == -1)
        {
            break;
        }
        if (huffman[j][3] < min2 && huffman[j][0] == -1 && j != ii[0])  
        {
            min2= huffman[j][3];
            ii[1] = j;
        }
    }
}

//�Ӻ����������ҽ��i�ĸ����,�õ���㵽���ĳ���
int findParent(int i,int huffman[][4],int n)
{
    int length = 0;
    if(huffman[i][0] == -1)     /*�ж��Ƿ�û�и���㣬û�и��ڵ㼴����Ϊ���ڵ㣬���жϸý�㱾���ǲ��Ǹ����*/
    {
        return 0;
    }
    length += (findParent(huffman[i][0],huffman,n) + 1);    //ͨ���ݹ�õ���㵽����·������
    return length;
}

//�Ӻ���������ÿ��Ҷ�ڵ���й��������벢���д�ӡ
void HuffmanCode(int i,int huffman[][4],int n)   //i<count  i++ѭ�� 
{
    char code[30];  //char����������
    int current=i;  //���嵱ǰ���ʵĽ��
    int father = huffman[i][0]; //���嵱ǰ���ĸ��ڵ�
    int start=0;    //ÿ�α����λ�ã���ʼΪ���뵹��λ��
    int first,last;     //char�����ͷ����β��
	
	int j=current=i;
    while(father != -1)
    {   
    	father = huffman[j][0];
    	
        if (huffman[father][1] == j)	//�жϵ�ǰ���ĸ�����������Ƿ�Ϊ��ǰ���
        {
            code[start] = '0';//�ӽ���Ǹ�����������������Ϊ0
        }
        else
            code[start] = '1';    //�ӽ���Ǹ�����������������Ϊ1

        j = father;		//����˷Դ�����µ�ǰ���
        father = huffman[j][0];	//ͬ����ǰ�����º󣩣����µ�ǰ���ĸ��׽��
                      
        start++;                        //���±���λ��
    }
    code[start]='\0';   //���������

    //��char�����е�Ԫ��ͷβ���˽��жԵ�
    for(first = 0, last = start-1; first < last; first++,last--)
    {
        //�Ե������ڲ�Ԫ��
        inplace_swap(&code[first], &code[last]);	/*�ú������Լ���д*/
    }

    printf("%c Huffman code:  %s\n",'A'+i,code);    //��ӡ�ַ���huffman����
}

//�Ӻ���������������char�����ݣ�ʹ���˲������㣩�����Լ������ÿɶ��ԽϺõķ�������ʵ�ָĺ���
void inplace_swap(char *x,char *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}
