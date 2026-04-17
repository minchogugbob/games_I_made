package game248;

import java.lang.Math;
import java.util.Scanner;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Main{
	static int[][] arr=new int[5][5];
	static int move=0;
	static int point=0;
	
	
//	빈자리에 랜덤으로 2 생성
	static void SetNum(){
		int x=(int)(Math.random()*3)+1;
		int y=(int)(Math.random()*3)+1;
		
//		2가 들어갈 공간이 있는지 확인
		boolean NoPlace=CheckPlace();
		if(NoPlace) Ending();
			
//		이 자리가 0이 아닐 때 다시 위치 정하기
		if(arr[x][y]!=0) {
			SetNum();
		}
		
		arr[x][y]=2;
		
//		현재 게임 상황 출력
		for(int i=0; i<5; i++) {
			for(int j=0; j<5; j++) {
				System.out.printf("%5d", arr[j][i]);
			}
			System.out.println();
		}
		System.out.println("your point: "+point);
		
		PushNum();
		
	}
	
//	숫자를 밀 방향 입력
	static void PushNum() {
		Scanner sc=new Scanner(System.in);
		
		System.out.println("\nex) w:위쪽, a:왼쪽, s:아래, d:오른쪽");
		System.out.printf("어느 방향으로 미시겠습니까?: ");
		
		String push=sc.next();
		
		switch(push) {
		case "w":
		case "W":
			move=1;
			break;
		case "a":
		case "A":
			move=3;
			break;
		case "s":
		case "S":
			move=4;
			break;
		case "d":
		case "D":
			move=2;
		}
		
		MoveNum();
		
	}
	
//	숫자 움직이기 & 합치기
	static void MoveNum(){
//		왼쪽
		if(move==3) {
			for(int i=0; i<5; i++) {
//			숫자 밀기	
				int a=0;
				for(int j=0; j<5; j++) {
					if(arr[i][j]==0) break;
					a++;
				}
				
				int b=a;
				for(int j=b; j<5; j++) {
					if(arr[j][i]!=0){
						arr[a][i]=arr[j][i];
						arr[j][i]=0;
						a++;
					}
				}
//				같은 숫자가 있으면 합치기
				for(int j=1; j<5; j++) {
					if(arr[j-1][i]!=0 && arr[j-1][i]==arr[j][i]) {
						point+=arr[j-1][i];
						arr[j-1][i]*=2;
						arr[j][i]=0;
					}
				}
//				숫자 밀기	
				a=0;
				for(int j=0; j<5; j++) {
					if(arr[i][j]==0) break;
					a++;
				}
				
				b=a;
				for(int j=b; j<5; j++) {
					if(arr[j][i]!=0){
						arr[a][i]=arr[j][i];
						arr[j][i]=0;
						a++;
						
					}
				}
			}
		}
//		오른쪽 정렬
		else if(move==2) {
			for(int i=0; i<5; i++) {
//				숫자 밀기	
				int a=4;
				for(int j=4; j>=0; j--) {
					if(arr[i][j]==0) break;
					a--;
				}
				
				int b=a;
				for(int j=b; j>=0; j--) {
					if(arr[j][i]!=0){
						arr[a][i]=arr[j][i];
						arr[j][i]=0;
						a--;
					}
				}
//				같은 숫자가 있으면 합치기
				for(int j=4; j>0; j--) {
					if(arr[j-1][i]!=0 && arr[j-1][i]==arr[j][i]) {
						point+=arr[j][i];
						arr[j][i]*=2;
						arr[j-1][i]=0;
					}
				}
//				숫자 밀기	
				a=4;
				for(int j=4; j>=0; j--) {
					if(arr[i][j]==0) break;
					a--;
				}
				
				b=a;
				for(int j=b; j>=0; j--) {
					if(arr[j][i]!=0){
						arr[a][i]=arr[j][i];
						arr[j][i]=0;
						a--;
					}
				}
			}
		}
//		위쪽 정렬
		else if(move==1) {
			for(int i=0; i<5; i++) {
//				숫자 밀기	
				int a=0;
				for(int j=0; j<5; j++) {
					if(arr[i][j]==0) break;
					a++;
				}
				
				int b=a;
				
				for(int j=b; j<5; j++) {
					if(arr[i][j]!=0){
						arr[i][a]=arr[i][j];
						arr[i][j]=0;
						a++;
					}
				}
//				같은 숫자가 있으면 합치기
				for(int j=1; j<5; j++) {
					if(arr[i][j]!=0 && arr[i][j]==arr[i][j-1]) {
						point+=arr[i][j-1];
						arr[i][j-1]*=2;
						arr[i][j]=0;
					}
				}
//				숫자 밀기	
				a=0;
				for(int j=0; j<5; j++) {
					if(arr[i][j]==0) break;
					a++;
				}
				
				b=a;
				for(int j=b; j<5; j++) {
					if(arr[i][j]!=0){
						arr[i][a]=arr[i][j];
						arr[i][j]=0;
						a++;
					}
				}
			}
		}
//		아래쪽 정렬
		else if(move==4) {
			for(int i=0; i<5; i++) {
//				숫자 밀기	
				int a=4;
				for(int j=4; j>=0; j--) {
					if(arr[i][j]==0) break;
					a--;
				}
				
				int b=a;
				for(int j=b; j>=0; j--) {
					if(arr[i][j]!=0){
						arr[i][a]=arr[i][j];
						arr[i][j]=0;
						a--;
					}
				}
//				같은 숫자가 있으면 합치기
				for(int j=4; j>0; j--) {
					if(arr[i][j-1]!=0 && arr[i][j-1]==arr[i][j]) {
						point+=arr[i][j];
						arr[i][j]*=2;
						arr[i][j-1]=0;
					}
				}
//			숫자 밀기	
				a=4;
				for(int j=4; j>=0; j--) {
					if(arr[i][j]==0) break;
					a--;
				}
				
				b=a;
				for(int j=b; j>=0; j--) {
					if(arr[i][j]!=0){
						arr[i][a]=arr[i][j];
						arr[i][j]=0;
						a--;
					}
				}
			}
		}
		
		SetNum();
	}
	
//	빈칸이 있는지 & 합칠 수 있는 숫자가 있는지
	static boolean CheckPlace() {
		boolean NoPlace=true;
		
//		0이 있는지 확인
		for(int i=0; i<5; i++) {
			for(int j=0; j<5; j++) {
				if(arr[j][i]==0) {
					NoPlace=false;
					break;
				}
			}
		}
		
//		합칠 수 있는 숫자가 있는지 확인
		if(NoPlace) {
			for(int i=0; i<5; i++) {
				for(int j=1; j<5; j++) {
					if(arr[j][i]==arr[j-1][i]) NoPlace=false;
					else if(arr[i][j]==arr[i][j-1]) NoPlace=false;
				}
			}
		}
		
		return NoPlace;
		
	}
	
//	게임 끝
	static void Ending() {
		System.out.println("Game Over!!!");
		System.out.println("Your final point : "+point);
		System.exit(0);
	}
	
//	시작
	public static void main(String[] args) {
		System.out.println("How to play: 같은 숫자를 방향키로 밀어 합쳐요.");
		System.out.println("\t\t더이상 밀 수 없을때까지 숫자를 합쳐보세요!!");
		
		for(int i=0; i<5; i++) {
			for(int j=0; j<5; j++) {
				arr[j][i]=0;
			}
		}
		
		SetNum();
		
	}

}
