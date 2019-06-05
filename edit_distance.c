/*H****************************************************************
* FILENAME :        edit_distance.c
*
* DESCRIPTION :
*       Calculates the edit distance between two strings 
*
* PUBLIC FUNCTIONS :
*       int     editDistance( char, char, int, int )
*
* NOTES :
*       This function computes the edit distance
*       by using a distance matrix.
*
*       Copyright 2017, Jacob Wilkins.  All rights reserved.
* 
* AUTHOR :    Jacob Wilkins        START DATE :    31 Oct 17
*
*H*/

#include <stdio.h>
#include <string.h>

int editDistance(char * str1, char * str2, int len1, int len2) {
  int distMat[len1 + 1][len2 + 1];
  int i, j;

  for (i = 0; i <= len1; i++) {
    distMat[i][0] = i;
  }
  for (i = 0; i <= len2; i++) {
    distMat[0][i] = i;
  }
  for (i = 1; i <= len1; i++) {
    char c1;
    c1 = str1[i-1];
    for (j = 1; j <= len2; j++) {
      char c2;
      c2 = str2[j-1];
      if (c1 == c2) {
        distMat[i][j] = distMat[i-1][j-1];
      }
      else {
        int insert, min, sub, del;
        del = 1 + distMat[i-1][j];
        insert = 1 + distMat[i][j-1];
        sub = 1 + distMat[i-1][j-1];
        min = del;
        if (insert < min) {
          min = insert;
        }
        if (sub < min) {
          min = sub;
        }
        distMat[i][j] = min;
      }
    }
  }
  printf("\n  |   |");
  int k, m, n;
  for (k = 0; k < len2; k++) {
    printf("  %c|", str2[k]);
  }
  printf("\n");
  for (k = 0; k < (len2*4)+7; k++) {
    printf("-");
  }
  printf("\n  |");
  for (k = 0; k < len2+1; k++) {
    printf("  %d|", distMat[0][k]);
  }
  printf("\n");
  for (k = 0; k < (len2*4)+7; k++) {
    printf("-");
  }
  printf("\n");
  for (k = 0; k < len1; k++) {
    printf(" %c|", str1[k]);
    for (m = 0; m < len2+1; m++) {
      printf("  %d|", distMat[k+1][m]);
    }
    printf("\n");
    for (n = 0; n < (len2*4)+7; n++) {
      printf("-");
    }
    printf("\n");
  }
  printf("\n");
  return distMat[len1][len2];
}

int main() {
  printf("Enter two words separated by a space (e.g.: cat someone).\n Stop with: -1 -1\n");
  while(1) {
    char str1[100];
    char str2[100];
    scanf("%s %s", str1, str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    printf(" first: %s\nsecond: %s\n", str1, str2);
    if ((strcmp(str1, "-1") == 0) || (strcmp(str2, "-1") == 0)) {
      return 0;
    }
    int ed = editDistance(str1, str2, len1, len2);
    printf("edit distance: %d\n", ed);
    printf("Alignment: \n");
    printf("\n========================================================================================\n");
  }
}
