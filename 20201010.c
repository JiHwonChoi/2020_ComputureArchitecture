#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>

struct REG {
	char c1;
	char c2;
	char c3;
	char c4;
}reg;

int binnum[8] = {0,};

void intoBinnum(int num)
{
	for (int test = 0; test < 8; test++)
	{
		binnum[test] = 0;
	}
	//bin num �ʱ�ȭ�� �ʿ��ϴ�;
	int numi = num;
	int position = 0;
	while (1) {
		binnum[position] = numi % 2;
		numi = numi / 2;
		position++;

		if (numi == 0)
		{ 
			break;

		}
			
	}
};


int main()
{

		FILE* in, *out;
		int ch;
		char str[33];
		int sam[5];
		int instnum = 0;
		
		out = fopen("test1.txt", "w");
		// test.bin �̶�� ���������� �б� �������� ����
		if ((in = fopen("test1.bin", "rb")) == NULL) {
			fputs("���� ���� ����!", stderr);
			exit(1);
		}


		// ���� ����, 1����Ʈ�� �о�, ���� ���
		/*while ((ch = fgetc(in)) != EOF) {
			printf("%02X ", ch);
		}
		*/

		while ((ch = fgetc(in)) != EOF) {
			reg.c1 = ch;
			sam[0] = ch;
			
			printf("reg.c1: %d\n", ch);
			intoBinnum(ch);
			for (int i = 7, j=0; i >= 0; i--)
			{
				str[j] = binnum[i]+'0';
				j++;
			}
			printf("%s\n", str);
			//ch�� ���� ���ڸ� ���̳ʸ� �ѹ�(8�ڸ�)�� �ٲ㼭
			//str�� 0~7���� �Է��ϱ�
			//bin num�� ����� �迭 0���� �ʱ�ȭ�ϱ�
			//str �迭�� 1010�� ĳ���ͷ� ����Ǿ�����
			
			ch = fgetc(in);
			reg.c2 = ch;
			sam[1] = ch;
			intoBinnum(ch);
			for (int i = 7, j = 8; i >= 0; i--)
			{
				str[j] = binnum[i] + '0';
				j++;
			}
			printf("%s\n", str);

			ch = fgetc(in);
			reg.c3 = ch;
			sam[2] = ch;
			intoBinnum(ch);
			for (int i = 7, j = 16; i >= 0; i--)
			{
				str[j] = binnum[i] + '0';
				j++;
			}
			printf("%s\n", str);


			ch = fgetc(in);
			reg.c4 = ch;
			sam[3] = ch;
			intoBinnum(ch);
			for (int i = 7, j=24; i >= 0; i--)
			{
				str[j] = binnum[i]+'0';
				j++;
			}
			
			str[32] = '\0';
			//str = 0101 32��Ʈ�� ����Ǿ�����, char �迭!
			printf("%s\n", str);
			fprintf(out, "inst %d: %02x%02x%02x%02x ", instnum, sam[0],sam[1], sam[2], sam[3]);
			instnum++;


		//str ó�� ������ �о 0�̸� ��Ÿ��
			int opcode =0;
			for (int i = 0; i < 6; i++)
			{
				opcode += (str[i]-'0') * pow(2,5-i);
			}
			if (opcode == 0)//rŸ��
			{
				//rŸ������ ����(5��Ʈ 2��)
				int rs = 0;
				for (int i = 6; i < 11; i++)
				{
					rs += (str[i] - '0') * pow(2, 10 - i);
				}
				//rs ��ȣ�ľ�
				printf("\n\nrs:%d\n\n", rs);


				int rt = 0;
				for (int i = 11; i < 16; i++)
				{
					rt += (str[i] - '0') * pow(2, 15 - i);
				}
				

				int rd = 0;
				for (int i = 16; i < 21; i++)
				{
					rd += (str[i] - '0') * pow(2, 20 - i);
				}
				

				int shamt = 0;
				for (int i = 21; i < 26; i++)
				{
					shamt += (str[i] - '0') * pow(2, 25 - i);
				}
				
				int funct = 0;
				for (int i = 26; i < 32; i++)
				{
					funct += (str[i] - '0') * pow(2, 31 - i);
				}
				
				fprintf(out, "\nfunt:%d\n", funct);

				switch (funct)
				{
				case 32:
					fprintf(out, "add $%d $%d $%d", rd, rs, rt);
					break;
				case 33:
					fprintf(out, "addd $%d $%d $%d", rd, rs, rt);
					break;
				case 36://and
					fprintf(out, "and $%d $%d $%d", rd, rs, rt);
					break;
				case 26://div
					fprintf(out, "div $%d $%d", rs, rt);
					break;
				case 27://divu
					fprintf(out, "divu $%d $%d", rs, rt);
					break;
				case 9://jalr
					fprintf(out, "jalr $%d $%d", rd, rs);
					break;
				case 8://jr
					fprintf(out, "jr $%d ", rs);
					break;
				case 16://mfhi
					fprintf(out, "mfhi $%d", rd);
					break;
				case 18://mflo
					fprintf(out, "mflo $%d", rd);
					break;
				case 17:
					fprintf(out, "mthi $%d", rs);
					break;
				case 19:
					fprintf(out, "mtlo $%d", rs);
					break;
				case 24:
					fprintf(out, "mult $%d $%d", rs, rt);
					break;
				case 25:
					fprintf(out, "multu $%d $%d", rs, rt);
					break;
				case 39:
					fprintf(out, "nor $%d $%d $%d", rd, rs, rt);
					break;
				case 37:
					fprintf(out, "or $%d $%d $%d", rd, rs, rt);
					break;
				case 0:
					fprintf(out, "sll $%d $%d %d", rd, rt, shamt);
					break;
				case 4:
					fprintf(out, "sllv $%d $%d $%d", rd, rt, rs);
					break;
				case 42:
					fprintf(out, "slt $%d $%d $%d", rd, rs, rt);
					break;
				case 43:
					fprintf(out, "sltu $%d $%d $%d", rd, rs, rt);
					break;
				case 3:
					fprintf(out, "sra $%d $%d %d", rd, rt, shamt);
					break;
				case 7:
					fprintf(out, "srab $%d $%d $%d", rd, rt, rs);
					break;
				case 2:
					fprintf(out, "srl $%d $%d %d", rd, rs, shamt);
					break;
				case 6:
					fprintf(out, "srlv $%d $%d %d", rd, rt, rs);
					break;
				case 34:
					fprintf(out, "sub $%d $%d %d", rd, rs, rt);
					break;
				case 35:
					fprintf(out, "subu $%d $%d %d", rd, rs, rt);
					break;
				case 12:
					fprintf(out, "syscall");

				default:
					fprintf(out, "unknown instruction");
					break;

				}

			}
			else //i Ÿ������ ���� (5��Ʈ 3��)
			{

			int rs = 0;
			for (int i = 6; i < 11; i++)
			{
				rs += (str[i] - '0') * pow(2, 10 - i);
			}
			//rs ��ȣ�ľ�
			printf("\n\nrs:%d\n\n", rs);


			int rt = 0;
			for (int i = 11; i < 16; i++)
			{
				rt += (str[i] - '0') * pow(2, 15 - i);
			}



			}

			fprintf(out, "\n");
		}// ������ ��ɾ� �� �� �����

		fclose(in); // ���� �ݱ�
	
	
	/*
	char s1[100];
	int num1;

	FILE* fp = fopen("test1.bin", "rb");

	fread(s1, sizeof(int), 1, fp);
	//fgets(s1, sizeof(s1), fp);
	
	for (int i = 0; i < 100; i++)
	{
		printf("%d\n", s1[i]);
	};

	fclose(fp);
	*/

	return 0;
}