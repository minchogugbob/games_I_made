#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#include<Windows.h>
#include<MMSystem.h>
#pragma comment(lib,"Winmm.lib")

#pragma warning (disable : 4996)
#define ESC 27
#define MAXENEMY 10
#define MAXBOSS 3
#define MAXBALL 20

int fx, fy, bx, by, score, hp = 3;
BOOL mujuk = FALSE;

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void CursorView(char show) {//커서숨기기
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void textcolor(int colorNum) { //글씨 색깔
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

//판정함수 자리

struct tag_Enemy {
	BOOL exist;
	BOOL move;
	int Type;
	int x, y;
	int nFrame;
	int nStay;
}
enemy[MAXENEMY];

struct tag_Boss {
	BOOL exist_boss;
	BOOL move_boss;
	int Type_boss;
	int x_boss, y_boss;
	int nFrame_boss;
	int nStay_boss;
	int hp_boss;
}
Boss[MAXBOSS];

struct tag_Ball {
	BOOL exist;
	int x, y;
	int nFrame;
	int nStay;
}
Ball[MAXBALL];

const char* arEnemy[] = { " ㅣ-ㅜ-ㅣ "," -_ㅜ_- ", " ㅡㅡㅜㅡㅡ ", " <-=-> " };
const char* arBoss[] = { " \\\\\\\----------ㅠ----------//// ",
				   " [[[[___ㅡㅡ__ㅠ__ㅡㅡ____]]]] " };

BOOL IsKeyDown(int Key) {
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
}


BOOL Opening() {
	gotoxy(0, 0);
	//system("mode con cols=74 lines=40 | title 10307_남궁비_10311_양정인");
	printf("\n");
	printf("    ######  ###  ##   #####    #####   ########  ####  ######    #####\n");
	printf("   ###  ##  ###  ##  ###  ##  ###  ##     ###     ###  ###  ##  ###  ##\n");
	printf("   ####     ###  ##  ###  ##  ###  ##     ###     ###  ###  ##  ###\n");
	printf("    #####   #######  ###  ##  ###  ##     ###     ###  ###  ##  ### ###\n");
	printf("      ####  ###  ##  ###  ##  ###  ##     ###     ###  ###  ##  ###  ##\n");
	printf("   ##  ###  ###  ##  ###  ##  ###  ##     ###     ###  ###  ##  ###  ##\n");
	printf("    #####   ###  ##   #####    #####      ###     ###  ###  ##   #####\n");

	printf("\n");
	printf("\t\t   #####      ####  ###  ##  ######\n");
	printf("\t\t  ###  ##    #####  ### ###  ###  ##\n");
	printf("\t\t  ###       ## ###  #######  ###\n");
	printf("\t\t  ### ###  ##  ###  ## # ##  #####\n");
	printf("\t\t  ###  ## ########  ## # ##  ###\n");
	printf("\t\t  ###  ## ##   ###  ##   ##  ###  ##\n");
	printf("\t\t   #####  ##   ###  ##   ##  ######\n");

	gotoxy(30, 30); printf(">");
	gotoxy(35, 30); printf("게임 시작");

	gotoxy(35, 35); printf("게임 설명");

	gotoxy(35, 40); printf("Alt + F4");

	int select = 0;
	int c;

	while (1) {
		if (_kbhit()) {        //키보드 입력 확인 (true / false)
			c = _getch();  // 새로 입력값을 판별하여 상하좌우 출력
			switch (c) {
			case 72:
				if (select == 0) select = 2;
				else select--;
				break;

			case 80:
				if (select == 2) select = 0;
				else select++;
				break;

			case 13:
				if (select == 0) {
					system("cls");
					return 0;
				}
				else if (select == 1) {
					system("cls");
					return 1;
				}
				else if (select == 2) {
					system("cls");
					exit(0);
				}
				break;

			case 32:
				system("mode con cols=102 lines=40| title 탈모비이이이이이임!!!!!!!!");
				printf("NX0000000KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKOollcc:;;::::;,,,;lk0KKKKKKKKKKKKKKKKKKKKKKKKK\n");
				printf("WNKKKKKKKKKKKKKKKKKKKKKKKXKKKKKKXXXXXXXXXXXXXXXXKKX0d:'..,:ccloddooolc;,';lOKKKKKKKKKKKKKKKKKKKKKKKK\n");
				printf("MNKKKKKKKKKKKXXXXXXXXXXKKK00OOKXXXXXXXXXXXXXXXXXKxl;. .'cdxkkkkkkkxxxxdoc;';d0KKKKKKKKKKKKKKKKKKKKKK\n");
				printf("MNKKKKKKXXXXXXXXXXXXXXXKOkxoldKXXXXXXXXXXXXXXXXOc.....cdkkOOOOOOOOkkkkkxxdl;;:d0KKKKKKKKKKKKKKKKKKKK\n");
				printf("WNKKKKKKXXXXXXXXXXXXXK0Oxdl:ckXXXXXXXXXXXXXXXXO:....'lxkkkOOOOOOOOOkkkkkxxdoc;';dKKKKKKKKKKKKKKKXXXX\n");
				printf("WNXKKXXXXXXXXXXXXXXXX0kdllccxKXXXXXXXXXXXNXXNKo....'oxkkkkkOOOO00OOOkkkkxxdolc,..dKKKXKXXXXXXXXXXXXX\n");
				printf("WNXXXXXXXXXXXXXXXNXX0OxolccxKXXXXXXXXXXXXXXXXO;...,cdxkkkkkOO00KK00OOkkxxddolc:. ,kXKXXXXXXXXXXXXXXX\n");
				printf("WNXXXXXXXXXXXXXXXXK0kdollcdKNXXXXXNNNXXNXXXXXk' .':ldxkkkkkOO00K000OOOkxxddlcc:,..dXXXXXXXXXXXXXXXXX\n");
				printf("WNXXKKKKKKXXXXNNNX0kdollco0NXNXXNNNNNNNXXXNXXx. .:odxxkxkkkO000000OOOOkxddolc::,..oXXXXXXXXXXXXXXXXX\n");
				printf("MNKKKK0OkxkOKKXXKOkxdoocl0NNNNNNNNNNNNNNNNNXO:..,oxxkkxdoooooxkOOOOOOOkkxdlc:::,..lKXXXXXXXXXXXXXXXX\n");
				printf("MNKKK0OkdolokOK0kxdddollONNNNNNNNNNNNNNNNNNKkc..:xkkkkxdlllcccoddxkkkkkxollc:;:, .dXXXXXXXXXXXXXXXXX\n");
				printf("MNKKK0koc::cokOkddddoloOXNNNNNNNNNNNNNNNNNNKOd,,oxkkkkkdoc:;:clodxxxddoc;,',;;:. ,OXXXXXXXXXXXXXXNNN\n");
				printf("MNK0Oxoc::cclodooooollkXNNNNNWWNNNNNNNNNXNNKOxclxkkkOO0Okxoc:cldxkdc:;;,;;,'';;..xXNXXNNNNNNNNNNNNNN\n");
				printf("MN0OxoccccccllooooolldKWWWWWWWWWWWWWWWNNNNNKOkxdxkkOO0K00OOkkkOO0Oo;::,'',;;::''xXXXNNNNNNNNNNNNNNNN\n");
				printf("MKxolc:cccllllloooollkNWWWWWWWWWWWWWWWWNNNNX0OxxxkOO0000OOOOOOO00Oocoddolc;;::ckXXXNNNNNNNNNNNNNNNNN\n");
				printf("M0olc::clllllllllllcckNWWWWWWWWMMWWWWWWWWWWNN0xxkkOOOOOOkxdxO0O00klclxkkxxocld0NNNNNNNNNNNNNNNNXXXNN\n");
				printf("M0olc::cllcllllllllc:dXWWWWWMMMMWWWWWWWWWWWWWKxkkkOOkkxdodxxddxOkdl:lxOOkxolkXNNNNNNNNNNNNNNXKKK00KN\n");
				printf("MKdolccccccccccllloocdXWWWMMMWMMMWWWWWWWWWNWWKxxkkkOOxoooxkkxdllc:;;cdkkxdoxKNNNNNNNNNNNNNNK0Okxod0N\n");
				printf("MKoolcc::;:::ccllooolo0NWWWWWWWWWWMWWWWWWWNWNOxxkkkkkxdoclddodoc:;,;coddoodKNNNNNNNNNNNNNX0kxdoloOXN\n");
				printf("MKollc::;;;;;:ccloddddxOKXNNNWWNWWWWWWWNNNWNKkxxxkkkkxxkxdxkkxdl:,':looold0XNNNNNNNNNNNXKOkdolld0NNN\n");
				printf("MKolllccc::::cclooddxkOO0KKKKXXXXXXNNXXNXKOOkxxxxxkkkkkkkxdoool:;,:looold0XNNNNNNNNNNNX0kxddooxKNNNN\n");
				printf("MKdooolllllclllloooddkOO00000KK00000KKXNKkxxkkkxxxxxxkOOOOxdoolccclloldOKNNNNNNNNNNNX0OkkdoookXNNNWW\n");
				printf("MKdoooooooooooooooooodxkkkOOOOOOkkkxxkXNKkkkkOkkxxdddxkOOOOkxddoolllokKNNNNNNNNNNNXKOkxxdddod0XXNNWW\n");
				printf("MKdoooooooooooooooooooodxxxxxddddooookXNXOkkOOOOkkxxdoddxxxxxdddollx0NNNNNWWNNWNNXKOkkxdddl,;odx0NWW\n");
				printf("MKdodddooooolllllcclolld00OkdoddxkOO0KXXN0kOOOOOOOkkxdoooolooollcccldk0XNWNNNNNNNKOkkkxkxo:,;:ccokKX\n");
				printf("MKdddddddooolllllllllccx0KKKkodddOKKKXXXNX0OOOOkkkkkxxddoolllcc::::ccccoxOKXKKKXK0kdddxxkkOkxdoccldx\n");
				printf("MXkddddddoooolllllllclok00KX0doooxOOOKXXXNKOOOOOkkxxddddollcc:;,;:cccccclodxkkkO0kxxdlldk0KK0Oxoclol\n");
				printf("MWN0ddddddoooollllllodkO00KKKkdooxkOOOKXXNXOOOOOOkxxdxxddolc;,,;cllllodxxxkO0000Okxkxc,ck000OOxlcodl\n");
				printf("WWWXxooddddooolllloxkkkOO0KKK0kxxkkkkk0KXNN0OOOOkkkkkOkxdoc:;coxkOOO000OOO000OOOOkkxl;;dOOkkxxoccddo\n");
				printf("MWWN0dddddddoooodxkkkkkOO000KKOkO0OkkkkOKXNX0kkkkkkkkkkxddodOK0OO0O00Okkkkkkxdxkkkxdloxkkkxddolloxxo\n");
				printf("MMMWNK0kxdddddxkkkkkkxxxkkO0KK0O00OOOkkxkO0K0kkkkkkkkkkkkkOKK0Okkkkxxxdddddoooodxxdoddxxdddooooxkxoc\n");
				printf("MMMWWWWNKkddxxkkkkkkdc::clokOOO000000OOkdxkkkxkkkkkkkOOOOkO0OkxkkOOddkkxxxxddoodddooolooolllloddoolc\n");
				printf("MMMMMWWMNOxxxkkkkkxxc''',,;:cokO0KK0000OxddoooxkkkkkOOOOkxxxddxxoxkdOKKK0O00kddddddooooooolooooooool\n");
				printf("MMMMMMWMW0kkkkkkkxxl'......,;:llkKKK000OOkdl:;:okOOOOOxloxllokkc;oxkKKK0OO00kxxkxdolodddddddddddddkO\n");
				printf("MMMMMMMMWXOkkkkkkxxc.......''...lOOOKK000OOkdoc,ckOOOx:':ccdO0d,,:d0KKKOk0KOxdxkxdllloooddddddooodON\n");
				printf("MMMMMMMMMNOkkkkkxkd;'...........,::coO000O00OOd;':odxxc.,oxOOo,',;dKK00OOKKkxddddoollooodddddooood0W\n");
				printf("MMMMMMMWMNOkOOOkxkl'................',lO00OOkxx:'codxo,'oOOxc'.,''oKK0OO0X0xdddoooolloooddddddoooxKN\n");
				printf("MMMMMMMMMXOOOOOkkkc.....''....,'.. ...:k0Okxdo:.;lool'.cO0xdc..,,.c0K0OOKX0xddooollllooodddddddookXW\n");
				printf("\n탈모빔을 맞으셨습니다! 10초안에 \"자라나라 머리머리!\"를 3번 외치지 않으면 당신을 탈모가 생깁니다!\n");
				break;
			}
			gotoxy(30, 30); printf("   ");
			gotoxy(30, 35); printf("   ");
			gotoxy(30, 40); printf("   ");
			gotoxy(30, 30 + 5 * select); printf(">");
		}
	}
}

void main() {

	int ch;
	int i, j;
	BOOL bFound;
	int  boss_kill = 0;
	int count;
	int boss_spawn = 0;
open:
	fx = 60;
	fy = 40;
	bx = -1;
	by = -1;
	score = 0;

	double mu_s, mu_e;

	system("mode con cols=77 lines=45 | title 10307_남궁비_10311_양정인");

	srand((unsigned)time(NULL));
	system("cls");
	CursorView(0);//커서 숨기기

	if (Opening()) {

		gotoxy(5, 13);
		printf("space를 눌러 적을 맞춰 점수를 최대한 얻는 게임입니다.\n");
		gotoxy(5, 15);
		printf("방향키를 눌러 왼/오른쪽으로 움직이면서 날아오는 총알을 피하세요!\n");
		gotoxy(5, 19);
		printf("가끔씩 보스가 출현합니다!!\n");
		gotoxy(5, 21);
		printf("보스가 나오면 다른 적들은 다 사라집니다.\n");
		gotoxy(5, 23);
		printf("(다른 적들은 보스를 다 죽이면 다시 나옵니다.)\n");
		gotoxy(5, 25);
		printf("보스는 3대를 맞춰야 사라집니다.\n");

		gotoxy(15, 43);
		printf("==============\"ESC\"를 눌러 뒤로가기==============");

		while (1) {
			ch = _getch();
			if (ch == ESC) {
				system("cls");

				goto open;
				break;
			}
		}

		while (1) {
			ch = _getch();
			if (ch == 13) {
				system("cls");
				break;
			}
		}
	}

	gotoxy(4, 41);
	for (int i = 0; i < 70; i++)
		printf("=");

	mciSendStringA("play ggcc_low.wav", NULL, 0, NULL);

	for (count = 0;; count++) {
		// 좌우 이동 처리
		if (count % 2 == 0) {
			if (IsKeyDown(VK_LEFT)) {
				if (fx > 6)
					fx--;
			}
			else if (IsKeyDown(VK_RIGHT)) {
				if (fx < 72)
					fx++;
			}

			else if (IsKeyDown(VK_UP)) {
				if (fy > 30)
					fy--;
			}
			else if (IsKeyDown(VK_DOWN)) {
				if (fy > 40)
					fy++;
			}
		}

		// 키 입력 처리``다운 80 업 72
		if (kbhit()) {
			ch = _getch();
			if (ch == 0xE0 || ch == 0) {
				_getch();
			}
			else {
				switch (ch) {
				case ' ': //Space

					//PlaySound(TEXT("MP_Blop.wav"), NULL, SND_ASYNC);
					if (bx == -1) {
						bx = fx;
						by = fy;
					} break;

					if (by == -1) {
						bx = fx;
						by = fy;
					} break;

				case ESC:
					goto end;
				}
			}
		}

		// 적군 생성
		if (boss_kill == 0){ 
			if (rand() % 50 == 0) {
				for (i = 0; i < MAXENEMY && enemy[i].exist == TRUE; i++) { ; }
				if (i != MAXENEMY) {
					if ((rand() % 2) + 1 == 1) {
						enemy[i].x = 5;
						enemy[i].move = 0;
					}
					else {
						enemy[i].x = 69;
						enemy[i].move = 1;
					}
					while (1) {
						enemy[i].y = rand() % 10 + 1;
						for (bFound = FALSE, j = 0; j < MAXENEMY; j++) {
							if (enemy[j].exist == TRUE && enemy[j].y == enemy[i].y) {
								bFound = TRUE;
								break;
							}
						}
						if (bFound == FALSE) {
							break;
						}
					}
					enemy[i].nFrame = enemy[i].nStay = rand() % 6 + 1;
					enemy[i].Type = rand() % (sizeof(arEnemy) / sizeof(arEnemy[0])); //random(sizeof(arEnemy) / sizeof(arEnemy[0]));
					enemy[i].exist = TRUE;
				}
			}
		}

		//보스 몹 출현
		// 보스몹에 맞게 값 변경 해야함
		// 보스몹 출현 확률 100, 보스몹 2개 중 하나를 출력 
		// 보스몹 잡으면 점수 +3
		//보스몹 출현시 몹 없어짐 : 남궁비 해줘 <-저런

		if (score %10==0 && score != 0) boss_kill++;

		if (boss_kill == 1) boss_spawn = rand() % MAXBOSS + 1;

		if (score == 10) boss_spawn = 1;

		if (boss_spawn) {
			for (i = 0; i < boss_spawn && Boss[i].exist_boss == TRUE; i++) { ; }
			if (i != boss_spawn) {
				if ((rand() % 2) + 1 == 1) {
					Boss[i].x_boss = 5 + 15;
					Boss[i].move_boss = 0;
				}
				else {
					Boss[i].x_boss = 75 - 15;
					Boss[i].move_boss = 0;
				}
				while (1) {
					Boss[i].y_boss = rand() % 10 + 1;
					for (bFound = FALSE, j = 0; j < boss_spawn; j++) {
						if (Boss[j].exist_boss == TRUE && Boss[i].y_boss == Boss[j].y_boss) {
							bFound = TRUE;
							break;
						}
					}
					if (bFound == FALSE) {
						break;
					}
				}
				Boss[i].nFrame_boss = Boss[i].nStay_boss = rand() % 6 + 1;
				Boss[i].Type_boss = rand() % (sizeof(arBoss) / sizeof(arBoss[0]));
				Boss[i].exist_boss = TRUE;
				Boss[i].hp_boss = 3;
			}
		}

		// 플레이어 이동 및 출력
		if (bx != -1) {
			gotoxy(bx, by);
			putch(' ');
			if (by == 0) {
				bx = -1;
			}
			else {
				by--;
				gotoxy(bx, by);
				if (by == 0) putch(' ');
				else
					putch('!');
			}
		}

		// 몹 플레이어 총알의 충돌 판정
		for (i = 0; i < MAXENEMY; i++) {
			if (enemy[i].exist == FALSE)
				continue;
			if (enemy[i].y == by && abs(enemy[i].x - bx) <= 4) {
				gotoxy(bx, by); putch(' ');
				bx = -1;
				enemy[i].exist = FALSE;
				gotoxy(enemy[i].x - 3, enemy[i].y);
				puts("             ");
				score += 1;
				break;
			}
		}
		// 보스 플레이어 총알의 충돌 판정
		for (i = 0; i < boss_spawn; i++) {
			if (Boss[i].exist_boss == FALSE)
				continue;

			if (Boss[i].y_boss == by && abs(Boss[i].x_boss - bx) <= 6) {
				Boss[i].hp_boss--;
				gotoxy(bx, by); putch(' ');
				bx = -1;
			}

			if (Boss[i].hp_boss == 0) {
				Boss[i].exist_boss = FALSE;
				gotoxy(Boss[i].x_boss - 15, Boss[i].y_boss);
				puts("                               ");
				score += 3;
				boss_spawn--;
			}

			if (!boss_spawn) break;
		}

		// 몹 총알 이동
		for (i = 0; i < MAXBALL; i++) {
			if (Ball[i].exist == FALSE)
				continue;
			if (--Ball[i].nStay == 0) {
				Ball[i].nStay = Ball[i].nFrame;
				gotoxy(Ball[i].x, Ball[i].y); putch(' ');
				if (Ball[i].y >= 40) {
					Ball[i].exist = FALSE;
				}
				else {
					Ball[i].y++;
					gotoxy(Ball[i].x, Ball[i].y); putch('*');
				}
			}
		}
		// 몹 총알 플레이어 총알 판정
		for (i = 0; i < MAXBALL; i++) {
			if (Ball[i].exist == FALSE)
				continue;
			if (Ball[i].y == 40 && abs(Ball[i].x - fx) <= 2 && !mujuk) {
				--hp;
				mujuk = TRUE;
				mu_s = clock() / CLOCKS_PER_SEC;
				PlaySound(TEXT("MP_실패 불안 (jingle).wav"), NULL, SND_ASYNC);
			}
			else if (hp == 0) {
				gotoxy(fx - 3, 38); puts("   .   ");
				gotoxy(fx - 3, 39); puts(" .  . .");
				gotoxy(fx - 3, 40); puts("..:V:..");
				Sleep(1000);

				goto end;
			}

			if (mujuk) {
				mu_e = (((double)clock()) / CLOCKS_PER_SEC);
				if (mu_e - mu_s >= 3) {
					mujuk = FALSE;
				}
			}

		}
		// 몹 이동, 공격
		for (i = 0; i < MAXENEMY; i++) {
			if (enemy[i].exist == FALSE)
				continue;
			if (--enemy[i].nStay == 0) {
				enemy[i].nStay = enemy[i].nFrame;

				if (!enemy[i].move) enemy[i].x++;
				else if (enemy[i].move) enemy[i].x--;

				gotoxy(enemy[i].x - 3, enemy[i].y);
				puts(arEnemy[enemy[i].Type]);

				if (enemy[i].x >= 70 || enemy[i].x <= 4) {
					enemy[i].exist = FALSE;
					gotoxy(enemy[i].x - 3, enemy[i].y);
					puts("           ");
				}

				else {
					// 총알 발사
					if (rand() % 20 == 0) {
						for (j = 0; j < MAXBALL && Ball[j].exist == TRUE; j++) { ; }
						if (j != MAXBALL) {
							Ball[j].x = enemy[i].x + 2;
							Ball[j].y = enemy[i].y + 1;
							Ball[j].nFrame = Ball[j].nStay = enemy[i].nFrame * 6;
							Ball[j].exist = TRUE;
						}
					}
				}
			}
		}

		//-----------------------------------------------------------------------------------------------
		// 보스 이동, 공격
		for (i = 0; i < boss_spawn; i++) {
			if (Boss[i].exist_boss == FALSE)
				continue;
			if (--Boss[i].nStay_boss == 0) {
				Boss[i].nStay_boss = Boss[i].nFrame_boss;
				if (Boss[i].x_boss >= 75 - 15 || Boss[i].x_boss <= 4 + 15) Boss[i].move_boss = !Boss[i].move_boss;

				if (!Boss[i].move_boss) Boss[i].x_boss++;
				else if (Boss[i].move_boss) Boss[i].x_boss--;

				gotoxy(Boss[i].x_boss - 15, Boss[i].y_boss);
				puts(arBoss[Boss[i].Type_boss]);

				gotoxy(Boss[i].x_boss - 2, Boss[i].y_boss);
				printf(" %d ", Boss[i].hp_boss);

				// 총알 발사
				if (rand() % 3 == 0) {
					for (j = 0; j < MAXBALL && Ball[j].exist == TRUE; j++) { ; }
					if (j != MAXBALL) {
						Ball[j].x = Boss[i].x_boss + 2;
						Ball[j].y = Boss[i].y_boss + 1;
						Ball[j].nFrame = Ball[j].nStay = Boss[i].nFrame_boss * 6;
						Ball[j].exist = TRUE;
					}
				}
			}
		}

		// 플레이어, 점수
		gotoxy(fx - 3, 40);
		if (mujuk)  textcolor(11);
		puts(" <<A>> ");
		textcolor(15);

		gotoxy(4, 42);
		printf("               ");
		gotoxy(4, 42);
		for (i = 0; i < hp; i++)
			printf("♥");
		gotoxy(4, 43);
		printf("your 실력 = % d", score);
		Sleep(40);
	}

end:
	PlaySound(TEXT("MP_실패 불안 (jingle).wav"), NULL, SND_ASYNC);
	system("cls");
	gotoxy(13, 10);
	printf("=====================게임 종료=====================\n\n");
	gotoxy(32, 15);
	printf("your 점수 = %d\n\n\n\n\n\n\n\n\n\n\n\n", score);
	gotoxy(32, 23);
	printf("재시작 = ESC");
	while (1) {
		ch = _getch();
		if (ch == ESC) {

			system("cls");

			goto open;
			break;
		}
	}
	CursorView(0);
}