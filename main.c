/*
 * Create on MacOS BigSur 11.1
 * 2021.2.6
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
//以下为Unix or Linux库
#include <unistd.h>
#include <sys/time.h>


/* 1、【题目】水仙花数
 * 水仙花数（Narcissistic number）又被称为阿姆斯特朗数（Armstrong number）。
 * 水仙花数是指一个3位数,它的每个位上的数字的3次幂之和等于它本身（例如：1^3 + 5^3+ 3^3 = 153）。
 * 答案：153,370,371,407
 */
/**
 * 水仙花数判断
 * @param x 需要判断的数字
 * @return bool型：是 true，否 false
 */
bool isNarcissistic(const int x) {
    int sum = 0, temp = x;
    while (temp) {
        sum += pow(temp % 10, 3);
        temp /= 10;
    }
    return sum == x;
}

void testIsNarcissistic() {
    for (int i = 100; i <= 999; ++i) {
        printf("%d is narcissistic ? ", i);
        isNarcissistic(i) ? printf("true\n") : printf("false\n");
    }
}

/* 扩展：
 * 水仙花数只是自幂数的一种,严格来说3位数的3次幂数才称为水仙花数。
 * 附：其他位数的自幂数名字
 * 一位自幂数：独身数 (全部)
 * 两位自幂数：没有
 * 三位自幂数：水仙花数 (153,370,371,407)
 * 四位自幂数：四叶玫瑰数 (1634,8208,9474)
 * 五位自幂数：五角星数 (54748,92727,93084)
 * 六位自幂数：六合数 (548834)
 * 七位自幂数：北斗七星数 (1741725,4210818,9800817,9926315)
 * 八位自幂数：八仙数 (24678050,24678051,8859347)
 * 九位自幂数：九九重阳数 (146511208,472335975,534494836,912985153)
 * 十位自幂数：十全十美数 (4679307774)
 */
/**
 * 自幂数判断
 * @param x 需要判断的数字
 * @param n 数字位数
 * @return bool型：是 true，否 false
 */
bool isSelfPower(const long long x, int n) {

    long long sum = 0L, temp = x;
    while (temp) {
        sum += pow(temp % 10, n);
        temp /= 10;

        if (sum > x) {  //提前结束
            return false;
        }
    }

    return sum == x;
}

void testIsSelfPower() {
    //计数，判断当前数字位数(1-9：9个数,10-99：90个数,100-999：900个数 ...)
    long long count = 9L, pre = 1L;
    int n = 1;    //数字位数
    for (long long i = 1L; i < 10000000000L; ++i) {
        if (i - pre == count) { //更新位数
            pre = i;
            count *= 10;
            n++;
        }
        if (isSelfPower(i, n)) {
            printf("%lld is SelfPower ? true\n", i);
        }
    }
}

/* 2、【题目】斐波那契数列
 * 古典问题：斐波那契数列（Fibonacci sequence），又称黄金分割数列,
 * 因数学家莱昂纳多·斐波那契（Leonardo Fibonacci）以兔子繁殖为例子而引入，故又称为“兔子数列”。
 * 有一对兔子，从出生后第3个月起每个月都生一对兔子，小兔子长到第三个月后每个月又生一对兔子，
 * 假如兔子都不死，问每个月的兔子总数为多少？
 * 兔子的规律为数列：0、1、1、2、3、5、8、13、21、34、........。
*/
/**
 * 计算斐波那契数列中的值
 * @param index 数列中的位序
 * @return 数列中的第n个值
 */
long long fibonacci(int index) {
    if (index <= 0 || index > 93) { //第93个数值long long会溢出
        return NAN;
    }

    //static减少非必要的重复计算（重复查询时），只依次往后计算到目标值，并保存已经计算出的值
    static long long result[100] = {0L, 1L, 1L};
    static int i = 3;
    for (; i < index; ++i) {
        //a[index]=a[index-1]+a[index-2]
        result[i] = result[i - 1] + result[i - 2];
    }

    return result[index - 1];
}

void testFibonacci() {
    for (int j = 0; j < 94; ++j) {
        printf("%lld\n", fibonacci(j));
    }
}

/*
 * 3、【题目】猴子吃桃问题
 * 猴子吃桃问题：猴子第一天吃了若干个桃子，当即吃了一半，还不解馋，又多吃了一个；
 * 第二天，吃剩下的桃子的一半，还不过瘾，又多吃了一个；以后每天都吃前一天剩下的一半多一个，
 * 到第10天想再吃时，只剩下一个桃子了。问第一天共吃了多少个桃子？
 * Day10------------------------1
 * Day9-------------------------4
 * Day8-------------------------10
 * Day7-------------------------22
 * Day6-------------------------46
 * Day5-------------------------94
 * Day4-------------------------190
 * Day3-------------------------382
 * Day2-------------------------766
 * Day1-------------------------1534
 */
/**
 * 计算猴子吃桃问题开始一共多少桃子
 * @param day 吃到只剩一个桃子需要的天数
 * @return 开始的桃子数
 */
int monkeyEatPeach(const int day) {

    if (day <= 1) {
        return 1;
    } else {
        //a[day-1]=a[day]/2-1   ==>     a[day]=(a[day-1]+1)*2
        return (monkeyEatPeach(day - 1) + 1) * 2;
    }
}

void testMonkeyEatPeach() {
    for (int i = 1; i <= 10; ++i) {
        printf("%d\n", monkeyEatPeach(i));
    }
}

/*
 * 4、【题目】物体自由落地
 * 一球从100米高度自由落下，每次落地后反跳回原高度的一半；
 * 再落下，求它在第10次落地时，共经过多少米？第10次反弹多高？
 */
/**
 * 计算自由落体从指定高度到第某次落地总弹跳距离和接下来的弹跳高度
 * @param height 指定初始落体高度
 * @param times 第几次落地
 * @return （long double [2]）{目前总弹跳距离，下次弹跳高度}
 */
long double *freeFall(const long double height, const int times) {
    long double h = height, sum = 100.0;
    int t = 2;
    while (t++ <= times && h > 0.0) {
        sum += h;
        h /= 2.0;
    }
    return (long double[2]) {sum, h / 2.0};
}

void testFreeFall() {
    for (int i = 1; i <= 30; ++i) {
        long double *temp = freeFall(100.0, i);
        printf("%d times sum:%Lf, %d bound height:%Lf\n", i, temp[0], i, temp[1]);
    }
}


/*
 * 5、【题目】矩阵对角线元素之和
 * 求一个3*3矩阵对角线元素之和
 */
/**
 * 计算矩阵（方阵）对角线元素和（使用了C99/C11的可选VLA特性）
 * @param n 矩阵维数
 * @param matrix 矩阵（二维数组存储）
 * @return 对角线元素和
 */
int matrixDiagSum(const int n, const int matrix[][n]) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += matrix[i][i];
    }
    return sum;
}

void testMatrixDiagSum() {
    int matrix[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
    };
    printf("%d\n", matrixDiagSum(3, matrix));
}

/*
 * 6、【题目】求素数
 * 判断101-200之间有多少个素数，并输出所有素数。
 */
/**
 * 判断一个数是否为素数（平方根范围取余判断）
 * @param x 待判断数字
 * @return bool型：是 true，否 false
 */
bool isPrime(int x) {
    if (x < 2) {
        return false;
    }

    int sqrt_x = sqrt(x);
    for (int i = 2; i <= sqrt_x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 * 统计指定范围内素数，并输出每个素数（ [x,y] ）
 * @param x 起始范围
 * @param y 终止范围
 * @return 素数个数
 */
int countPrime(int x, int y) {
    int count = 0;
    for (int i = x; i <= y; ++i) {
        if (isPrime(i)) {
            printf("%d ", i);
            count++;
        }
    }
    return count;
}

void testCountPrime() {
    printf("\n%d\n", countPrime(100, 200));
}

/*
 * 扩展：埃氏筛法
 */
/**
 * 埃氏筛法求素数
 * @param result 接受素数结果的数组
 * @param p 筛选素数的辅助数组
 * @param n 范围上限（ (2，n] ）
 * @param len 素数个数
 */
void sieve(int prime[], bool p[], const int n, int *const restrict count) {
    *count = 0;   //初始素数个数为0
    for (int i = 2; i <= n; ++i) {  //从2开始筛
        if (!p[i]) {    //i为素数
            prime[(*count)++] = i;   //加入接受素数结果数组，素数个数加一
            for (int j = i + i; j <= n; j += i) {   //筛掉i的倍数
                p[j] = true;
            }
        }
    }
}

void testSieve() {
    const int max = 10240;   //数组大小
    static int prime[max] = {0};   //保存素数结果数组
    static bool p[max] = {0};   //p[i]==false 则i为素数，反之非素数
    int count = 0;  //素数个数

    sieve(prime, p, 1, &count);
    for (int i = 0; i < count; ++i) {
        printf("%d ", prime[i]);
    }
    printf("\n%d\n", count);

    sieve(prime, p, 2, &count);
    for (int i = 0; i < count; ++i) {
        printf("%d ", prime[i]);
    }
    printf("\n%d\n", count);

    sieve(prime, p, 1000, &count);
    for (int i = 0; i < count; ++i) {
        printf("%d ", prime[i]);
    }
    printf("\n%d\n", count);
}

/*
 * 7、【题目】分解质因数
 * 将一个正整数分解质因数。
 * 例如：输入90,打印出90=2*3*3*5。
 */
/**
 * 分解质因数并打印结果
 * @param n 待分解数字
 */
void primeFactorsSimple(const int n) {
    int temp = n;
    printf("%d=", temp);
    for (int i = 2; i <= temp; i++) {
        while (temp != i) {
            if (temp % i == 0) {
                printf("%d*", i);
                temp = temp / i;
            } else {
                break;
            }
        }
    }
    if (temp != n) {
        printf("%d\n", temp);
    } else {
        printf("can't resolve!\n");
    }
}

void testPrimeFactorsSimple() {
    for (int i = 1; i <= 10000; ++i) {
        primeFactorsSimple(i);
    }
}

/**
 * 分解质因数（通过质数表分解，更高效）
 * @param result 分解结果的质因子数组（第一列为 因子，第二列为 该因子个数）
 * @param count 不同质因子个数（用来遍历质因子数组）
 * @param prime 质数表
 * @param n 待分解数字
 */
void primeFactors(int result[][2], int *restrict count, const int prime[], const int n) {

    *count = 0;
    int sqrt_n = sqrt(n);
    int temp = n;

    for (int i = 0; prime[i] <= sqrt_n; ++i) {  //遍历质数表，只需遍历到待分解数的平方根

        if (temp % prime[i] == 0) { //可整除的某一质数
            result[*count][0] = prime[i];
            result[*count][1] = 0;
            while (temp % prime[i] == 0) {//计数可整除的某同一质数个数
                result[*count][1]++;
                temp /= prime[i];
            }
            (*count)++; //该质数不可继续整除，质因子个数加一
        }

        if (temp == 1) {    //若已经分解到1，则分解结束
            break;
        }
    }

    //待分解数的开方值及之前的质数尚未将其分解完，则分解到最后(非1非自身)的数即是最后一个质因子
    if (temp != 1 && temp != n) {
        result[*count][0] = temp;
        result[*count][1] = 1;
        (*count)++;
    }

}

void testPrimeFactors() {
    const int max = 10240;   //数组大小
    static int prime[max / 2] = {0};   //保存素数结果数组
    static bool p[max] = {0};   //p[i]==false 则i为素数，反之非素数
    int countP = 0, countF = 0;  //素数个数
    int result[10][2] = {0};    //int范围不同因子个数不会超过10个（2*3*5*...*29 > int）

    sieve(prime, p, 1000, &countP); //先获取质数表

    for (int i = 1; i <= 10000; ++i) {
        primeFactors(result, &countF, prime, i);    //分解
        if (countF > 0) {
            printf("%d=", i);
            for (int j = 0; j < countF; ++j) {
                while (result[j][1]-- > 0) {
                    printf("%d", result[j][0]);
                    if (result[j][1] > 0) {
                        printf("*");
                    }
                }
                if (j < countF - 1) {
                    printf("*");
                }
            }
        } else {
            printf("%d can't resolve!", i);
        }
        printf("\n");
    }
}

/*
 *8、【题目】完数
 * 完全数（Perfect number），又称完美数或完备数，是一些特殊的自然数。
 * 它所有的真因子（即除了自身以外的约数）的和（即因子函数），恰好等于它本身。
 * 例如6=1＋2＋3.编程找出1000以内的所有完数:6,28,49。
 */
/**
 * 判断是否为完全数
 * @param x 待判断数
 * @return bool型：是true，否false
 */
bool perfectNumber(const int x) {

    int sum = 0;
    for (int i = 1; i < x; ++i) { //遍历所有数
        if (x % i == 0) {   //因子
            sum += i;
        }
    }
    if (sum == x) {
        return true;
    } else {
        return false;
    }
}

void testPerfectNumber() {
    for (int i = 1; i <= 1000; ++i) {
        if (perfectNumber(i)) {
            printf("%d\n", i);
        }
    }
}

/**
 * 查找完全数（使用欧拉推导公式，更高效）
 * @param result 结果数组
 * @param count 结果数组长度
 * @param primer 素数存储数组
 * @param p 素数判断辅助数组
 * @param n 查找范围上限
 */
void findPerfectNumber(int result[], int *const restrict count, const int primer[], const bool p[], const int n) {
    int temp;
    *count = 0;
    //如果p是质数，且2^p-1也是质数,2^p-1称为梅森素数。
    //欧拉曾推算出完全数的获得公式：如果p是质数，且2^p-1也是质数，那么（2^p-1）X2^（p-1）便是一个完全数。
    for (int i = 0; (temp = pow(2, primer[i]) - 1) < n; ++i) {  //遍历素数表
        if (!p[temp]) {
            result[(*count)++] = temp * pow(2, primer[i] - 1);
        }
    }
}

void testFindPerfectNumber() {
    const int max = 10240;   //数组大小
    static int prime[max / 2] = {0};   //保存素数结果数组
    static bool p[max] = {0};   //p[i]==false 则i为素数，反之非素数
    int countP = 0, countR = 0;  //素数个数
    int result[50] = {0};

    sieve(prime, p, 1000, &countP); //先获取质数表

    findPerfectNumber(result, &countR, prime, p, 1000);
    for (int i = 0; i < countR; ++i) {
        printf("%d\n", result[i]);
    }

}


/*
 * 9、【题目】最大公约数和最小公倍数
 * 输入两个正整数m和n，求其最大公约数和最小公倍数。
 * 最大公约数：gcd(a,b)=gcd(b,a%b）
 * 最小公倍数：lcm(a,b)=a*b/gcd(a,b)  (避免溢出，先除后乘)
 */
/**
 * 求最大公约数（递归）
 * @param a 待求数字
 * @param b 待求数字
 * @return 最大公约数
 */
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;   //递归结束条件b==0，返回结果a
}
/**
 * 求最小公倍数（递归）
 * @param a 待求数字
 * @param b 待求数字
 * @return 最小公倍数
 */
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

void testGCDLCM(){
    for (int i = 1; i < 10; ++i) {
        int temp=i+rand()%100+1;
        printf("%d,%d gcd:%d,lcm:%d\n",i,temp,gcd(i,temp),lcm(i,temp));
    }
}

/**
 * 求最大公约数和最小公倍数（非递归）
 * @param a 待求数字
 * @param b 待求数字
 */
void gcdAndLcm(int a,int b){
    int n1=a,n2=b,temp;
    if (n1<n2){
        temp=n2;
        n2=n1;
        n1=temp;
    }
    while (n2){
        temp=n1%n2;
        n1=n2;
        n2=temp;
    }
    printf("%d,%d gcd:%d,lcm:%d\n",a,b,n1,a/n1*b);
}

void testGcdAndLcm(){
    for (int i = 1; i < 10; ++i) {
        int temp=i+rand()%100+1;
        gcdAndLcm(i,temp);
    }
}




int main() {

    srand((unsigned )time(NULL));

    /* time()精确到秒
    time_t start,end;
    start=time(NULL);
    printf("start:%ld\n",start);
    sleep(1); //可以影响time()计时
    end=time(NULL);
    printf("start:%ld\n",end);
    printf("time spend:%ld s\n",end-start);
    */

    /* clock()在Unix or Linux下不计时sleep
    printf("%d\n",CLOCKS_PER_SEC); //一秒多少个计时单元
    clock_t start, end;
    start = clock();
    printf("start:%lu\n",start);
    sleep(1); //不影响clock()计时
    end = clock();
    printf("end:%lu\n",end);
    printf("time spend:%f ms\n", (end - start)*1000.0/CLOCKS_PER_SEC);
    */

    /* Unix or Linux : sys/time.h
    strut timeval
    {
        long tv_sec; // 秒数
        long tv_usec; // 微秒数
    };
    */
    struct timeval start, end;
    gettimeofday(&start, 0); //参数：接受时间的结构体，时区设置

    //sleep(1);
    //testIsNarcissistic();
    //testIsSelfPower();
    //testFibonacci();
    //testMonkeyEatPeach();
    //testFreeFall();
    //testMatrixDiagSum();
    //testCountPrime();
    //testSieve();
    //testPrimeFactorsSimple();
    //testPrimeFactors();
    //testPerfectNumber();
    //testFindPerfectNumber();
    //testGCDLCM();
    testGcdAndLcm();


    gettimeofday(&end, 0);
    double timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;    //微秒数
    timeuse /= 1000; //除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时
    printf("%f ms", timeuse);

    return 0;
}
