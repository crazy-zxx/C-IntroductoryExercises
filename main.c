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
#include <ctype.h>
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
    long double h = height, sum = height;
    int t = 2;
    while (t++ <= times && h > 0) {
        sum += h;
        h /= 2;
    }
    return (long double[2]) {sum, h / 2};
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
 * 扩展：埃氏筛法求素数
 */
/**
 * 埃氏筛法求素数
 * @param prime 接受素数结果的数组
 * @param p 筛选素数的辅助数组
 * @param n 范围上限（ (2，n] ）
 * @param count 素数个数
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
 * 正整数分解质因数并打印结果
 * @param n 待分解数字
 */
void primeFactorsSimple(const int n) {
    if (n < 2 || isPrime(n)) {
        printf("%d=can't resolve!\n", n);
        return;
    }

    int temp = n;
    printf("%d=", temp);
    for (int i = 2; i <= temp; i++) {
        while (temp % i == 0) {
            printf("%d", i);
            temp /= i;
            if (temp != 1) {
                printf("*");
            } else {
                printf("\n");
                return;
            }
        }
    }
}

void testPrimeFactorsSimple() {
    for (int i = 0; i <= 10000; ++i) {
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
void primeFactors(int n) {

    const int max = 102400;   //质数查找范围上限大小
    static int prime[max / 2] = {0};   //质数表
    int countP = 0;            //质数个数
    static int p[max] = {0};   //辅助数组，p[i]==0 则i为质数，反之非质数

    sieve(prime, p, max, &countP); //先获取质数表

    //数值校验
    if (n < 2 || n >= max || !p[n]) {
        printf("%d can't resolve!\n", n);
        return;
    }

    int temp = n;
    int sqrt_n = sqrt(n);
    printf("%d = ", n);
    //分解质因数
    //遍历质数表，只需遍历到待分解数的平方根
    for (int i = 0; prime[i] <= sqrt_n; ++i) {
        if (temp % prime[i] == 0) {         //可整除的某一质数
            while (temp % prime[i] == 0) {  //输出完可整除的某同一质数
                printf("%d", prime[i]);
                temp /= prime[i];

                if (temp == 1) { //已经分解到1，结束
                    printf("\n");
                    return;
                } else {        //尚可继续分解
                    printf("*");
                }
            }
        }
    }

    //待分解数的开方值及之前的质数尚未将其分解完，
    //则分解到最后(非1非自身)的数即是最后一个质因子
    if (temp != 1 && temp != n) {
        printf("%d\n", temp);
    }

}

void testPrimeFactors() {

    for (int i = 1; i <= 1000; ++i) {
        primeFactors(i);
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
int gcd(const int a, const int b) {
    return b ? gcd(b, a % b) : a;   //递归结束条件b==0，返回结果a
}

/**
 * 求最小公倍数（递归）
 * @param a 待求数字
 * @param b 待求数字
 * @return 最小公倍数
 */
int lcm(const int a, const int b) {
    return a / gcd(a, b) * b;
}

void testGCDLCM() {
    for (int i = 1; i < 10; ++i) {
        int temp = i + rand() % 100 + 1;
        printf("%d,%d gcd:%d,lcm:%d\n", i, temp, gcd(i, temp), lcm(i, temp));
    }
}

/**
 * 求最大公约数和最小公倍数（非递归）
 * @param a 待求数字
 * @param b 待求数字
 */
void gcdAndLcm(const int a, const int b) {
    int n1 = a, n2 = b, temp;
    if (n1 < n2) {  //保证 n1 > n2
        temp = n2;
        n2 = n1;
        n1 = temp;
    }
    while (n2) {    //辗转相除法（又名欧几里德算法）
        temp = n1 % n2;
        n1 = n2;
        n2 = temp;
    }
    printf("%d,%d gcd:%d,lcm:%d\n", a, b, n1, a / n1 * b);
}

void testGcdAndLcm() {
    for (int i = 1; i < 10; ++i) {
        int temp = i + rand() % 100 + 1;
        gcdAndLcm(i, temp);
    }
}

/*
 * 10、【题目】三个数由小到大输出
 */
/**
 * 三个数由小到大输出
 * @param a 待处理数字
 * @param b 待处理数字
 * @param c 待处理数字
 */
void sortThreeNumber(const int a, const int b, const int c) {

    int num[] = {a, b, c};  //映射到数组
    int min = 0, max = 0;    //标记最小、最大值下标
    for (int i = 0; i < 3; ++i) {   //遍历，查找最小最大值
        if (num[i] < num[min]) {   //确定最小值下标
            min = i;
        } else if (num[i] > num[max]) {    //确定最大值下标
            max = i;
        }
    }
    printf("%3d,", num[min]);
    printf("%3d,", num[3 - min - max]);
    printf("%3d\n", num[max]);
}

void testSortThreeNumber() {
    for (int i = 0; i < 10; ++i) {
        int a[3] = {rand() % 100, rand() % 100, rand() % 100};
        printf("%3d,%3d,%3d: ", a[0], a[1], a[2]);
        sortThreeNumber(a[0], a[1], a[2]);
    }
}

/*
 * 11、【题目】企业发放的奖金根据利润提成
 * 利润(I)低于或等于10万元时，奖金可提10%；
 * 利润高于10万元，低于20万元时，低于10万元的部分按10%提成，高于10万元的部分，可提成7.5%；
 * 20万到40万之间时，高于20万元的部分，可提成5%；
 * 40万到60万之间时高于40万元的部分，可提成3%；
 * 60万到100万之间时，高于60万元的部分，可提成1.5%;
 * 高于100万元时，超过100万元的部分按1%提成。
 * 从键盘输入当月利润I，求应发放奖金总数？
 */
/**
 * 计算奖金（根据利润提成）
 * @param i 利润
 * @return 奖金
 */
double getBonus(double i) {

    int bonus1 = 100000 * 0.1;
    int bonus2 = bonus1 + (200000 - 100000) * 0.075;
    int bonus4 = bonus2 + (400000 - 200000) * 0.05;
    int bonus6 = bonus4 + (600000 - 400000) * 0.03;
    int bonus10 = bonus6 + (1000000 - 600000) * 0.015;

    double bonus = 0.0;
    if (i <= 100000.0) {
        bonus = i * 0.1;
    } else if (i < 200000.0) {
        bonus = (i - 100000.0) * 0.075 + bonus1;
    } else if (i < 400000.0) {
        bonus = (i - 200000.0) * 0.05 + bonus2;
    } else if (i < 600000.0) {
        bonus = (i - 400000.0) * 0.03 + bonus4;
    } else if (i < 1000000.0) {
        bonus = (i - 600000.0) * 0.015 + bonus6;
    } else {
        bonus = (i - 1000000.0) * 0.01 + bonus10;
    }

    return bonus;
}

void testGetBonus() {
    double temp = 0.0;
    for (int i = 0; i <= 11; ++i) {
        printf("%-10.2f, %-10.2f\n", temp, getBonus(temp));
        temp += 100000.0;
    }
}

/*
 * 12、【题目】判断这一天是这一年的第几天
 * 输入某年某月某日，判断这一天是这一年的第几天？
 */
/**
 * 计算某一天是这一年的第几天
 * @param year 待判断的年
 * @param month 待判断的月
 * @param day 待判断的日
 * @return 这一年的第几天
 */
int dayOfYear(int year, int month, int day) {

    int days = 0;
    int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};    //每月天数
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {     //闰年把2月加一天
        monthDays[2]++;
    }
    //累计之前月的天数
    for (int i = 1; i < month; ++i) {
        days += monthDays[i];
    }
    //加当前月份天数
    days += day;

    return days;
}

void testDayOfYear() {
    for (int i = 0; i < 10; ++i) {
        int y = rand() % (2100 - 2000) + 2000;
        int m = rand() % 12 + 1;
        int d = rand() % 28 + 1;
        printf("%4d.%02d.%02d: %d\n", y, m, d, dayOfYear(y, m, d));
    }
    printf("2000.03.01: %d\n", dayOfYear(2000, 3, 1));
}

/*
 * 13、【题目】排列无重复数字的三位数(1234)
 * 有1、2、3、4个数字，能组成多少个互不相同且无重复数字的三位数？都是多少？
 */
/**
 * 排列无重复数字的三位数(穷举判断)
 */
void notRepeatThreeDigitsSimple() {
    for (int i = 1; i < 5; i++) {       // 以下为三重循环
        for (int j = 1; j < 5; j++) {
            for (int k = 1; k < 5; k++) {
                if (i != k && i != j && j != k) // 确保i、j、k三位互不相同
                    printf("%d,%d,%d\n", i, j, k);
            }
        }
    }
}

void testNotRepeatThreeDigitsSimple() {
    notRepeatThreeDigitsSimple();
}

/**
 * 排列无重复数字的三位数(递归)
 * @param result 暂存每次排列结果
 * @param p 辅助判断数组（下标对应排列用数字，值代表该数字是否已经用过）
 * @param index 起始位置（默认从第一位开始排列数字，勿用其他值）
 * @param bits 需要的排列结果位数
 * @param count 排列可用数字个数(如 1个：1；4个：1，2，3，4)
 */
void notRepeatThreeDigits(int result[], bool p[], const int index, const int bits, const int count) {
    if (index > bits) { //排列完指定位数后，打印当前结果
        for (int i = 1; i <= bits; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
        return;
    } else {    //继续排列
        for (int i = 1; i <= count; ++i) {  //遍历所有可用数字
            if (!p[i]) {    //只用之前未使用的数字
                p[i] = true;    //标记使用
                result[index] = i; //加入暂存结果的数组
                notRepeatThreeDigits(result, p, index + 1, bits, count);
                p[i] = false;   //用完取消使用标记，使得以后递归可再用，必须要有！！！
            }
        }
    }
}

void testNotRepeatThreeDigits() {

    bool p[5] = {0};
    int num[5] = {0};

    notRepeatThreeDigits(num, p, 1, 3, 2);
    printf("\n");
    notRepeatThreeDigits(num, p, 1, 3, 3);
    printf("\n");
    notRepeatThreeDigits(num, p, 1, 3, 4);
}

/*
 * 14、【题目】输出9*9口诀乘法表
 */
/**
 * 打印9*9口诀乘法表
 */
void printMultiplicationTable() {
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= i; ++j) {
            printf("%d*%d=%-2d  ", j, i, i * j);
        }
        printf("\n");
    }
}

void testPrintMultiplicationTable() {
    printMultiplicationTable();
}

/*
 * 15、【题目】打印出菱形图案
 * 空格数目：l/2 ，...（每次减一），最长行为0，...（每次加一）
 * 星号数目：1   ，...（每次加二），最长行为l，...（每次减二）
 *         *
 *        ***
 *       *****
 *      *******
 *       *****
 *        ***
 *         *
 */
/**
 * 打印出菱形图案
 * @param l 行数(奇数)
 */
void printRhombus(int l) {

    int asterisk = 1; //初始第一行星号数目
    int blank = l / 2;  //初始第一行星号前空格数目
    for (int i = 1; i <= l / 2 + 1; ++i) {  //前一半加一行
        for (int j = 1; j <= blank; ++j) {
            printf(" ");
        }
        for (int j = 1; j <= asterisk; ++j) {
            printf("*");
        }
        blank--;        //下一行空白数目减一
        asterisk += 2;    //下一行星号数目加二
        printf("\n");
    }
    //调整数目
    asterisk = l - 2;
    blank = 1;
    for (int i = l / 2; i >= 1; --i) {    //后一半减一行
        for (int j = 1; j <= blank; ++j) {
            printf(" ");
        }
        for (int j = 1; j <= asterisk; ++j) {
            printf("*");
        }
        blank++;        //下一行空白数目加一
        asterisk -= 2;    //下一行星号数目减二
        printf("\n");
    }
}

void testPrintRhombus() {
    for (int i = 1; i <= 11; i += 2) {
        printRhombus(i);
    }
}

/*
 * 16、【题目】输出国际象棋棋盘
 */
void printChessBoard() {
    int a, b;
    for (a = 1; a <= 8; a++) {
        for (b = 1; b <= 8; b++) {
            if ((b + a) % 2 == 0) {
                printf("□");
            } else {
                printf("■");
            }
        }
        printf("\n");
    }
}

void testPrintChessBoard() {
    printChessBoard();
}

/*
 * 17、【题目】统计出字母_空格_数字_其它字符个数
 * 输入一行字符，分别统计出字母、空格、数字和其它字符个。
 */
void calcCountOfStr(const char *restrict input) {
    int alpha_count = 0, space_count = 0, digit_count = 0, other_count = 0;
    while (*input != '\n') {
        if (isalpha(*input)) {
            alpha_count++;
        } else if (*input == ' ') {
            space_count++;
        } else if (isdigit(*input)) {
            digit_count++;
        } else {
            other_count++;
        }
        input++;
    }
    printf("alpha: %d, space: %d, digit: %d, other: %d\n", alpha_count, space_count, digit_count, other_count);
}

void testCalcCountOfStr() {
    calcCountOfStr("qwert   123;''//=-*.\n");
}

/*
 * 18、【题目】分数序列
 * 有一分数序列：2/1，3/2，5/3，8/5，13/8，21/13...求出这个数列的前20项之和。(斐波那契)
 */
double fractionSum(const int n) {
    int fibo[1024] = {1, 1};   //存储斐波那契数列
    for (int i = 2; i <= n + 1; ++i) {    //计算斐波那契数列
        fibo[i] = fibo[i - 2] + fibo[i - 1];
    }

    double sum = 0.0;
    for (int i = 1; i <= n; ++i) {      //计算分数和
        sum += fibo[i + 1] * 1.0 / fibo[i];
    }
    return sum;
}

void testFractionSum() {
    for (int i = 1; i <= 20; ++i) {
        printf("sum of %d items: %f\n", i, fractionSum(i));
    }
}

/*
 * 19、【题目】求阶乘
 */
/**
 * 计算阶乘（递归，容易溢出堆栈）
 * @param x 待求值
 * @return 阶乘
 */
int factorial(const int x) {
    if (x < 0) {
        return NAN;
    }
    if (x <= 1) {
        return 1;
    } else {
        return x * factorial(x - 1);
    }
}

void testFactorial() {
    for (int i = 0; i <= 10; ++i) {
        printf("%d's factorial is : %d\n", i, factorial(i));
    }
}

/**
 * 计算阶乘（循环）
 * @param x 待求值
 * @return 阶乘
 */
long double factorialLoop(const int x) {

    if (x < 0) {
        return NAN;
    }
    if (x > 1754) {    //阶乘溢出类型值
        return INFINITY;
    }

    long double result = 1.0;
    for (int i = 2; i <= x; ++i) {
        result *= i;
    }

    return result;
}

void testFactorialLoop() {
    printf("%d's factorial is : %.0Lf\n", 10, factorialLoop(10));
    printf("%d's factorial is : %.0Lf\n", 100, factorialLoop(100));
    printf("%d's factorial is : %.0Lf\n", 1754, factorialLoop(1754));
}

/*
 * 20、【题目】回文数
 * 例如：一个5位数，判断它是不是回文数。即12321是回文数，个位与万位相同，十位与千位相同。
 */
/**
 * 判断是否为回文数
 * @param x 待判断数字
 * @return bool型：是true，否false
 */
bool isPalindrome(const int x) {
    char temp[16] = {0};
    sprintf(temp, "%d", x);
    //自己实现数字映射为字符串，略费时
    //int n = x;
    //for (int i = 0; n && i < 16; ++i) {
    //    temp[i] = n % 10;
    //    n /= 10;
    //}
    int len = strlen(temp);
    for (int i = 0; i < len / 2; ++i) {
        if (temp[i] != temp[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

void testIsPalindrome() {
    for (int i = -100; i < 1000; ++i) {
        if (isPalindrome(i)) {
            printf("%d\n", i);
        }
    }
}

/*
 * 21、【题目】求同数多项之和
 * 求s=a+aa+aaa+aaaa+aa...a的值，其中a是一个数字。
 * 例如2+22+222+2222+22222(此时共有5个数相加)
 */
/**
 * 求同数多项之和
 * @param x 构成数的数字（取值0-9）
 * @param bits 构成的最大数字位数
 * @return 同数多项之和
 */
int sameNumberSum(const int x, const int bits) {

    if (x < 0 || x > 9 || bits < 0 || bits > 9) {
        return -1;
    }

    int result = 0;
    int temp = x, n = bits;
    while (n--) {
        result += temp;
        temp = temp * 10 + x;
    }

    return result;
}

void testSameNumberSum() {
    for (int i = 0; i < 10; ++i) {
        int x = rand() % 9 + 1;
        int bits = rand() % 9 + 1;
        printf("%d bits %d : %d\n", bits, x, sameNumberSum(x, bits));
    }
    printf("9 bits 9 : %d\n", sameNumberSum(9, 9));
}

/*
 * 22、【题目】求100之内的素数,同6题
 */
void testPrimeHundred() {
    for (int i = 0; i <= 100; ++i) {
        if (isPrime(i)) {
            printf("%d\n", i);
        }
    }
}

/*
 * 23、【题目】数组逆序输出
 */
/**
 * 逆序输出数组元素
 * @param arr 待输出数组
 * @param n 数组元素个数
 */
void printReverseArr(const int arr[], const int n) {
    for (int i = n - 1; i >= 0; --i) {
        printf("%3d ", arr[i]);
    }
}

void testPrintReverseArr() {
    int temp[10] = {0};
    for (int i = 0; i < 10; ++i) {
        for (int i = 0; i < 10; ++i) {
            temp[i] = rand() % 100;
            printf("%3d ", temp[i]);
        }
        printf("\n");
        printReverseArr(temp, 10);
        printf("\n\n");
    }
}

/**
 * 翻转数组
 * @param arr 待处理数组
 * @param n 数组元素个数
 */
void reverseArr(int arr[], int n) {
    for (int i = 0; i < n / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}

void testReverseArr() {
    int temp[10] = {0};
    for (int i = 0; i < 10; ++i) {
        for (int i = 0; i < 10; ++i) {
            temp[i] = rand() % 100;
            printf("%3d ", temp[i]);
        }
        printf("\n");
        reverseArr(temp, 10);
        for (int i = 0; i < 10; ++i) {
            printf("%3d ", temp[i]);
        }
        printf("\n\n");
    }
}

/*
 * 24、【题目】将有序数组插入数字仍然有序。
 * 现有已排好序的数组，将输入一个数，要求按原来的规律将它插入数组中。
 */
/**
 * 将数字插入有序数组，仍然保持有序
 * @param arr 有序数组（请自行保证足够容纳）
 * @param n 数组长度
 * @param x 插入值
 */
void insertArr(int arr[], int n, int x) {
    if (n > 0) {
        if (n <= 1 || arr[0] <= arr[1]) {
            for (int i = 0; i < n; ++i) {
                if (x <= arr[i]) {  //找到第一个大于等于插入值的数字，该位置就是插入位置
                    for (int j = n - 1; j >= i; --j) {  //后移
                        arr[j + 1] = arr[j];
                    }
                    arr[i] = x; //插入
                    return;
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                if (x > arr[i]) {  //找到第一个大于等于插入值的数字，该位置就是插入位置
                    for (int j = n - 1; j >= i; --j) {  //后移
                        arr[j + 1] = arr[j];
                    }
                    arr[i] = x; //插入
                    return;
                }
            }
        }

    }
}

void testInsertArr() {

    for (int i = 0; i < 10; ++i) {
        int temp[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int i = 0; i < 10; ++i) {
            printf("%2d ", temp[i]);
        }
        insertArr(temp, 10, i);
        printf("\ninsert %d to array:\n", i);
        for (int i = 0; i < 11; ++i) {
            printf("%2d ", temp[i]);
        }
        printf("\n\n");
    }

    for (int i = 0; i < 10; ++i) {
        int temp[15] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        for (int i = 0; i < 10; ++i) {
            printf("%2d ", temp[i]);
        }
        insertArr(temp, 10, i);
        printf("\ninsert %d to array:\n", i);
        for (int i = 0; i < 11; ++i) {
            printf("%2d ", temp[i]);
        }
        printf("\n\n");
    }
}


/*
 * 25、【题目】static用法
 */
void staticFun() {
    int var = 0;
    static int static_var = 0;
    printf("\nvar :%d \n", var);
    printf("static var :%d \n", static_var);
    var++;
    static_var++;
}

void testStaticFun() {
    printf("\n【普通变量和静态变量区别】\n");
    for (int i = 0; i < 3; i++) {
        staticFun();
    }
}

/*
 * 26、【题目】auto用法
 */
void autoFun() {
    int i, num;
    num = 2;
    for (i = 0; i < 3; i++) {
        printf("The num equal %d \n", num);
        num++;
        {
            auto int num = 1;
            printf("The internal block num equal %d \n\n", num);
            num++;
        }
    }
}

void testAutoFun() {
    autoFun();
}

/*
 * 27、【题目】extern用法
 */
int a_e = 5, b_e, c_e;

void externFun() {
    extern int a_e;
    //a_e = 3;
    c_e = a_e + b_e;
}

void testExternFun() {
    b_e = 4;
    externFun();
    printf("\nThe value of c_e is equal to %d\n\n", c_e);
}

/*
 * 28、【题目】register用法
 */
void registerFun() {
    register int i;
    int tmp = 0;
    for (i = 1; i <= 100; i++) {
        tmp += i;
    }
    //printf("The register address is %p\n", &i);   //无法获取register变量地址
    printf("The sum is %d\n", tmp);
}

void testRegisterFun() {
    registerFun();
}

/*
 * 29、【题目】宏define命令
 */
#define TRUE 1
#define FALSE 0
#define SQ(x) ((x)*(x))

void defineFun() {
    int num;
    int again = 1;
    while (again) {
        printf("Please input number-->:(>=50 loop)");
        scanf("%d", &num);
        printf("The square for this number is %d \n", SQ(num));
        if (num >= 50) {
            again = TRUE;
        } else {
            again = FALSE;
        }
    }
}

void testDefineFun() {
    defineFun();
}

/*
 * 30、【题目】累积项之和
 * 求1+2!+...+n!的和。
 */
long double factorialSum(const int n) {
    long double sum = 0.0, temp = 1.0;
    for (int i = 1; i <= n; ++i) {
        temp *= i;
        sum += temp;
    }
    return sum;
}

void testFactorialSum() {
    for (int i = 1; i <= 10; ++i) {
        printf("%d items sum: %.0Lf\n", i, factorialSum(i));
    }
}

/*
 * 31、【题目】温度转换
 * 热力学温度（又称开氏温度）(T)、华氏温度(F)、摄氏温度（C）的换算式
 * T = (5/9) × (F - 32) + 273.15
 * F = (9/5) × (T - 273.15) + 32
 * C = (5/9) × F + 32
 */
/**
 * 温度转换(开氏温度T、华氏温度F、摄氏温度C换算)
 * @param T 开氏温度
 * @param F 华氏温度
 * @param C 摄氏温度
 * @param n 指明以第几个参数作为参考转换为其他温度
 */
void temperatureTrans(double *const restrict T, double *const restrict F,
                      double *const restrict C, const int n) {

    if (n == 1) {
        *F = 9.0 / 5 * ((*T) - 273.15) + 32;
        *C = (5.0 / 9) * ((*F) - 32);
    } else if (n == 2) {
        *T = (5.0 / 9) * ((*F) - 32) + 273.15;
        *C = (5.0 / 9) * ((*F) - 32);
    } else if (n == 3) {
        *F = 1.8 * (*C) + 32;
        *T = (5.0 / 9) * ((*F) - 32) + 273.15;
    } else {
        printf("Error!");
        return;
    }
}

void testTemperatureTrans() {
    printf(" 开氏             华氏              摄氏 \n");
    double a[3] = {100};
    temperatureTrans(&a[0], &a[1], &a[2], 1);
    for (int j = 0; j < 3; ++j) {
        printf(" %-15.2f ", a[j]);
    }
    printf("\n");

    double b[3] = {0, 100};
    temperatureTrans(&b[0], &b[1], &b[2], 2);
    for (int j = 0; j < 3; ++j) {
        printf(" %-15.2f ", b[j]);
    }
    printf("\n");

    double c[3] = {0, 0, 100};
    temperatureTrans(&c[0], &c[1], &c[2], 3);
    for (int j = 0; j < 3; ++j) {
        printf(" %-15.2f ", c[j]);
    }
    printf("\n");
}

/*
 * 32、【题目】计算存款利息
 * 假设有本金1000元，想存一年，有三种方法可选择：
 * 活期，年利率为0.0036；
 * 一年期定期，年利率为0.0225；
 * 存两次半年定期，年利率为0.0198。
 * 请分别计算出一年后按3种方法所得到的本息和
 */
/**
 * 计算存款利息
 * @param capital 本金
 */
void saveInterests(const double capital) {

    if (capital < 0) {
        printf("Error!\n");
        return;
    }

    double rate1 = 0.0036;
    double rate2 = 0.0225;
    double rate3 = 0.0198;

    double money1 = capital * (1 + rate1);
    double money2 = capital * (1 + rate2);
    double money3 = capital * (1 + rate3 / 2) * (1 + rate3 / 2);

    printf("%.2f : %.2f,%.2f,%.2f\n", capital, money1, money2, money3);
}

void testSaveInterests() {
    saveInterests(-10);
    saveInterests(0);
    saveInterests(10);
    saveInterests(1000);
}

/*
 * 33、【题目】判断某一年是否是闰年
 */
/**
 * 判断是否为闰年
 * @param year 年份
 * @return bool型：是true，否false
 */
bool isLeapYear(const int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return true;
    } else {
        return false;
    }
}

void testIsLeapYear() {
    for (int i = 1900; i < 2030; ++i) {
        if (isLeapYear(i)) {
            printf("%d is leap year\n", i);
        }
    }
}

/*
 * 34、【题目】杨辉三角
 */
/**
 * 打印杨辉三角（二维数组，极其浪费空间）
 * @param n 行数
 */
void printYHTriangle(const int n) {
    if (n <= 0 || n > 99) {
        printf("Error!\n");
        return;
    }

    int t[100][100] = {0};    //二维数组保存（极其浪费空间，可用俩数组相互交换数据，实时打印）
    t[1][1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (j > 1 && j <= i) {
                t[i][j] = t[i - 1][j - 1] + t[i - 1][j];
            } else {
                t[i][j] = t[i - 1][j];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            printf(" %5d ", t[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void testPrintYHTriangle() {
    for (int i = 0; i <= 10; ++i) {
        printYHTriangle(i);
    }
}

/**
 * 打印杨辉三角（两数组，节省空间）
 * @param n 行数
 */
void printYHTriangle2(const int n) {

    if (n <= 0) {
        printf("Error!\n");
        return;
    }

    unsigned long long t[1024] = {0}, temp[1024] = {0, 1};
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            t[j] = temp[j - 1] + temp[j];
            printf(" %5llu ", t[j]);
        }
        for (int j = 1; j <= i; ++j) {
            temp[j] = t[j];
        }
        printf("\n");
    }
    printf("\n");
}

void testPrintYHTriangle2() {
    for (int i = 0; i <= 10; ++i) {
        printYHTriangle2(i);
    }
}

/*
 * 36、【题目】完全平方数
 * x = n^2 >= 0，则x为完全平方数
 */
/**
 * 判断是否是完全平方数
 * @param x 待判断数值
 * @return bool型：是true，否false
 */
bool isPerfectSquare(const int x) {
    if (x >= 0 && (int) pow((int) sqrt(x), 2) == x) {
        return true;
    }
    return false;
}

void testIsPerfectSquare() {
    for (int i = 0; i < 1000; ++i) {
        if (isPerfectSquare(i)) {
            printf("%d\n", i);
        }
    }
}

/*
 * 36、【题目】一个整数，它加上100后是一个完全平方数，再加上168又是一个完全平方数，请问该数是多少？
 * x+100=m^2
 * x+268=n^2
 * ==> n^2-m^2=(n+m)(n-m)=168
 * ==> n+m=i,n-m=j,i*j=168
 * ==> n=(i+j)/2,m=(i-j)/2
 * ==> i,j都是偶数,且i>=j>=2
 * ==> 2<=i<=168/2=84,j=168/i
 */
/**
 * 求解整数，它加上100后是一个完全平方数，再加上168又是一个完全平方数
 */
void calcOnePerfectSquare() {
    for (int i = 84; i >= 2; i -= 2) {
        int j = 168 / i;
        int n = (i + j) / 2;
        int m = (i - j) / 2;
        if (i >= j && n * n - 268 == m * m - 100) {
            printf("%d\n", n * n - 268);
        }
    }
}

void testCalcOnePerfectSquare() {
    calcOnePerfectSquare();
}

/*
 * 37、【题目】乒乓球比赛
 * 两个乒乓球队进行比赛，各出三人。甲队为a,b,c三人，乙队为x,y,z三人。
 * a说他不和x比，c说他不和x,z比，请编程序找出三队赛手的名单。
 */
/**
 * 乒乓球比赛方案
 */
void testPingPangGame() {
    char i, j, k;
    for (i = 'x'; i <= 'z'; i++) {                 //a的对手
        for (j = 'x'; j <= 'z'; j++) {             //b的对手
            if (i != j) {                      //a，b对手不同
                for (k = 'x'; k <= 'z'; k++) {     //c的对手
                    if (i != k && j != k) {        //a，b和c对手不同
                        if (i != 'x' && k != 'x' && k != 'z') {    //a不和x比，c不和x,z比
                            printf("顺序为：a--%c , b--%c , c--%c\n", i, j, k);
                        }
                    }
                }
            }
        }
    }
}

/*
 * 37、【题目】分解正整数
 * 要求：一、求它是几位数，二、逆序打印出各位数字。
 */
/**
 * 分解正整数
 * @param x 待处理数值
 */
void resolveInt(const int x) {
    int count = 0;
    int n = x;
    while (n) {
        printf("%d", n % 10);
        n /= 10;
        count++;
    }
    printf(" %d bits\n", count);
}

void testResolveInt() {
    resolveInt(100);
    resolveInt(1234);
    resolveInt(13579);
    resolveInt(246810);
}

/*
 *  38、【题目】判断星期
 *  请输入星期几的第一个字母来判断一下是星期几，如果第一个字母一样，则继续判断第二个字母
 */
void testDayOfTheWeek() {
    char i, j;
    printf("请输入第一个字母:\n");
    scanf("%c", &i);
    getchar();
    switch (i) {
        case 'm':
        case 'M':
            printf("monday\n");
            break;
        case 'w':
        case 'W':
            printf("wednesday\n");
            break;
        case 'f':
        case 'F':
            printf("friday\n");
            break;
        case 't':
        case 'T':
            printf("请输入下一个字母\n");
            scanf("%c", &j);
            if (j == 'u') {
                printf("tuesday\n");
                break;
            }
            if (j == 'h') {
                printf("thursday\n");
                break;
            }
        case 's':
        case 'S':
            printf("请输入下一个字母\n");
            scanf("%c", &j);
            if (j == 'a') {
                printf("saturday\n");
                break;
            }
            if (j == 'u') {
                printf("sunday\n");
                break;
            }
        default :
            printf("error\n");
            break;
    }
}

/*
 * 38、【题目】删除字符
 * 删除一个字符串中的指定字符，如：字符串 "aca"，删除其中的 a 字符。
 */
/**
 * 删除一个字符串中的指定字符（不修改源字符串）
 * @param str 字符串
 * @param ch 指定字符
 * @return 删除后的新字符串
 */
char *deleteChar(const char *str, const char ch) {

    if (!str) {
        return NULL;
    }

    int len = strlen(str);
    char *result = (char *) malloc(sizeof(char) * (len + 1));
    int count = 0;
    for (int i = 0; i < len; ++i) {
        if (str[i] != ch) {
            result[count++] = str[i];
        }
    }
    result[count] = '\0';
    return result;
}

void testDeleteChar() {
    puts(deleteChar("aba", 'a'));
    puts(deleteChar("abcdedcfs", 'd'));
    puts(deleteChar("apple", 'p'));
    puts(deleteChar("aba", 'f'));
}

/*
 * 39、【题目】排序
 * 对10个数进行排序。
 */
/**
 * 直接插入排序算法
 * @param arr 待排序数组
 * @param n 元素个数
 */
void insertSort(int arr[], const int n) {

    for (int i = 1; i < n; ++i) {   //从第二个元素开始插入
        if (arr[i] < arr[i - 1]) {  //待插入的值 小于 已有序部分的最后一个，需要继续向前比较
            int temp = arr[i];        //暂存待插入值，
            arr[i] = arr[i - 1];        //向后移动已有序部分的最后元素
            int j;
            for (j = i - 2; temp < arr[j] && j >= 0; --j) { //继续向前比较
                arr[j + 1] = arr[j];    //向后移动有序部分
            }
            arr[j + 1] = temp;          //插入
        }
    }
}

/**
 * 二分（折半）插入排序算法
 * @param arr 待排序数组
 * @param n 元素个数
 */
void binaryInsertSort(int arr[], const int n) {

    for (int i = 1; i < n; ++i) {       //从第二个元素开始插入
        int temp = arr[i];
        int low = 0, high = i - 1;      //有序区间
        while (low <= high) {           //low <= high
            int mid = (low + high) / 2;
            if (arr[i] < arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        for (int j = i - 1; j > high; --j) {  //后移有序部分
            arr[j + 1] = arr[j];
        }
        arr[low] = temp;       //插入（插入位置为low==high+1）
    }
}

/**
 * 希尔排序算法
 * @param arr 待排序数组
 * @param n 元素个数
 */
void shellSort(int arr[], const int n) {

    for (int i = n / 2; i > 0; i /= 2) {    //折半增量：n/2，n/4，... ，1
        for (int j = i; j < n; j += i) {    //间隔增量成组比较直插
            if (arr[j] < arr[j - i]) {
                int temp = arr[j];
                int k;
                for (k = j - i; temp < arr[k] && k >= 0; k -= i) {    //继续向前比较
                    arr[k + i] = arr[k];
                }
                arr[k + i] = temp;
            }
        }
    }
}

/**
 * 冒泡排序算法
 * @param arr 待排序数组
 * @param n 元素个数
 */
void bubbleSort(int arr[], const int n) {

    for (int i = 1; i < n; ++i) {
        bool flag = true;
        for (int j = 1; j < n; ++j) {
            if (arr[j - 1] > arr[j]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                flag = false;
            }
        }
        if (flag) {
            break;
        }
    }
}

/**
 * 快排一次划分
 * @param arr 待排序数组
 * @param low 下界
 * @param high 上界
 * @return 一次划分后枢纽的下标
 */
int partition(int arr[], int low, int high) {
    int temp = arr[low];
    while (low < high) {
        while (low < high && arr[high] > temp) {
            high--;
        }
        arr[low] = arr[high];
        while (low < high && arr[low] < temp) {
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = temp;
    return low;
}

/**
 * 快排递归处理
 * @param arr 待排序数组
 * @param low 下界
 * @param high 上界
 */
void QSort(int arr[], const int low, const int high) {
    if (low < high) {
        int pos = partition(arr, low, high);
        QSort(arr, low, pos - 1);
        QSort(arr, pos + 1, high);
    }
}

/**
 * 快速排序算法
 * @param arr 待排序数组
 * @param n 元素个数
 */
void quickSort(int arr[], const int n) {
    QSort(arr, 0, n - 1);
}

/**
 * 简单选择排序算法
 * @param arr 待排序数组
 * @param n 元素个数
 */
void selectSort(int arr[], const int n) {

    for (int i = 0; i < n - 1; ++i) {
        int temp = arr[i];
        int minPos = i;       //最小值下标
        for (int j = i + 1; j < n; ++j) { //找最小值下标
            if (arr[j] < arr[minPos]) {
                minPos = j;
            }
        }
        if (minPos != i) { //交换
            arr[i] = arr[minPos];
            arr[minPos] = temp;
        }
    }
}

/**
 * 将部分元素调整为大顶堆
 * @param arr 待调整数组
 * @param start 起始下标（包括）
 * @param end 结束下标（包括）
 */
void adjustBigHeap(int arr[], int start, int end) {

    int temp = arr[start];

    for (int i = 2 * start; i <= end; i *= 2) { //层层向下判断调整
        if (i < end && arr[i] < arr[i + 1]) {  //寻找两个孩子最大值
            i++;
        }
        if (temp >= arr[i]) {  //双亲结点比两个子节点大，不需调整
            break;
        }
        arr[start] = arr[i];  //调整，父与大数值孩子换位

        start = i;    //继续沿当前孩子分支向下判断
    }
    arr[start] = temp;    //插入原堆顶到合适位置
}

/**
 * 堆排序算法
 * @param arr 待排序数组
 * @param n 元素个数
 */
void heapSort(int arr[], const int n) {

    for (int i = (n - 1) / 2; i >= 0; --i) {    //建大顶堆
        adjustBigHeap(arr, i, n - 1);
    }

    for (int i = 1; i < n; ++i) {   //取出堆顶元素，将[0,n-i]重新调整为大顶堆
        int temp = arr[0];
        arr[0] = arr[n - i];
        arr[n - i] = temp;

        adjustBigHeap(arr, 0, n - 1 - i);
    }

}

/**
 * 合并两个有序序列为一个有序序列:sArr[l..m,m+1..n] ==> tArr[l,n]
 * @param sArr 源数组
 * @param tArr 目的数组
 * @param l 起始下标（包括）
 * @param m 中间下标
 * @param n 终止下标（包括）
 */
void merge(int sArr[], int tArr[], int l, const int m, const int n) {
    int i;  //遍历sArr右半部分
    int j;  //遍历tArr数组
    //l遍历sArr左半部分
    for (i = m + 1, j = l; i <= n && l <= m; ++j) {    //升序归并两部分，两者取小作为当前需要插入值
        if (sArr[l] <= sArr[i]) {
            tArr[j] = sArr[l++];
        } else {
            tArr[j] = sArr[i++];
        }
    }
    while (l <= m) {   //如左半部分有剩余，追加
        tArr[j++] = sArr[l++];
    }
    while (i <= n) {   //如右半部分有剩余，追加
        tArr[j++] = sArr[i++];
    }
}

/**
 * 二路归并（递归）:sArr[s..t] ==> tArr[s..t]
 * @param sArr 源数组
 * @param tArr 目的数组
 * @param s 起始下标（包括）
 * @param t 终止下标（包括）
 */
void MSort(int sArr[], int tArr[], const int s, const int t) {

    if (s == t) {               //只有一个元素，不需归并
        tArr[s] = sArr[s];
    } else {
        int temp[1024] = {0};   //临时数组，用于暂存归并序列
        int mid = (s + t) / 2;
        MSort(sArr, temp, s, mid);              //左递归归并
        MSort(sArr, temp, mid + 1, t);        //右递归归并
        merge(temp, tArr, s, mid, t);           //归并左右两部分
    }
}

/**
 * 二路归并排序算法
 * @param arr 待排序数组
 * @param n 元素个数
 */
void mergeSort(int arr[], const int n) {

    MSort(arr, arr, 0, n - 1);

}

/**
 * 提供给qsort的比较函数
 * @param a 第一个参数
 * @param b 第二个参数
 * @return a-b
 */
int compare(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

/**
 * 调用库函数qsort排序
 * @param arr 待排序数组
 * @param n 元素个数
 */
void qsortN(int arr[], const int n) {

    qsort(arr, n, sizeof(int), compare);
}

/**
 * 打印数组元素
 * @param arr 待打印数组
 * @param n 元素个数
 */
void printArr(int arr[], const int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void testSortTenNumber() {

    int a[10] = {1, 3, 8, 6, 4, 5, 9, 2, 0, 7};
    printArr(a, 10);
    insertSort(a, 10);
    printArr(a, 10);
    printf("\n");

    int b[10] = {1, 3, 8, 6, 4, 5, 9, 2, 0, 7};
    printArr(b, 10);
    binaryInsertSort(b, 10);
    printArr(b, 10);
    printf("\n");

    int c[10] = {1, 3, 8, 6, 4, 5, 9, 2, 0, 7};
    printArr(c, 10);
    shellSort(c, 10);
    printArr(c, 10);
    printf("\n");

    int d[10] = {1, 3, 8, 6, 4, 5, 9, 2, 0, 7};
    printArr(d, 10);
    bubbleSort(d, 10);
    printArr(d, 10);
    printf("\n");

    int e[10] = {1, 3, 8, 6, 4, 5, 9, 2, 0, 7};
    printArr(e, 10);
    quickSort(e, 10);
    printArr(e, 10);
    printf("\n");

    int f[10] = {1, 3, 8, 6, 4, 5, 9, 2, 0, 7};
    printArr(f, 10);
    selectSort(f, 10);
    printArr(f, 10);
    printf("\n");

    int g[10] = {1, 3, 8, 6, 4, 5, 9, 2, 0, 7};
    printArr(g, 10);
    heapSort(g, 10);
    printArr(g, 10);
    printf("\n");

    int h[10] = {1, 3, 8, 6, 4, 5, 9, 2, 0, 7};
    printArr(h, 10);
    mergeSort(h, 10);
    printArr(h, 10);
    printf("\n");

    int i[10] = {1, 3, 8, 6, 4, 5, 9, 2, 0, 7};
    printArr(i, 10);
    qsortN(i, 10);
    printArr(i, 10);
    printf("\n");

}


/*
 * 40、【题目】交换最值
 * 将一个数组，最大的与第一个元素交换，最小的与最后一个元素交换，输出数组。
 */
void minMaxSwitch(int arr[], const int n) {
    int min = 0, max = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[min]) {
            min = i;
        } else if (arr[i] > arr[max]) {
            max = i;
        }
    }
    int temp = arr[min];
    arr[min] = arr[n - 1];
    arr[n - 1] = temp;

    temp = arr[max];
    arr[max] = arr[0];
    arr[0] = temp;
}

void testMinMaxSwitch() {

    int a[8] = {1, 3, 2, 8, 7, 6, 5, 0};
    printArr(a, 8);
    minMaxSwitch(a, 8);
    printArr(a, 8);

}

/*
 * 41、【题目】数组循环移位
 * 有 n 个整数，使其前面各数顺序向后移 m 个位置，最后m个数变成最前面的 m 个数。
 * 实现原理：每部分各自转置再整体转置，或先整体转置再各部分转置
 * 例如：1234 56 ==> 56 1234
 * 过程如下：
 * ① 1234 ==> 4321
 * ② 56 ==> 65
 * ③ 432165 ==> 561234
 */
/**
 * 转置（翻转）数组
 * @param arr 待处理数组
 * @param start 起始下标（包括）
 * @param end 结束下标（包括）
 */
void reverseArr2(int arr[], const int start, const int end) {
    for (int i = start; i < (end + start + 1) / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[end + start - i];
        arr[end + start - i] = temp;
    }
}

/**
 * 循环移动数组指定位数
 * @param arr 待处理数组
 * @param n 元素个数
 * @param m 移动最后几位
 */
void loopMoveArr(int arr[], const int n, const int m) {
    reverseArr2(arr, 0, n - m - 1);
    reverseArr2(arr, n - m, n - 1);
    reverseArr2(arr, 0, n - 1);
}

void testLoopMoveArr() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    printArr(arr, 6);
    loopMoveArr(arr, 6, 2);
    printArr(arr, 6);
}

/*
 * 42、【题目】约瑟夫环
 * 有n个人围成一圈，顺序排号。从第一个人开始报数（从1到3报数），凡报到3的人退出圈子，问最后留下的是原来第几号的那位。
 */
/**
 * 约瑟夫环求生还者原始序号
 * @param n 人数
 * @param m 该死的数
 * @return 生还者序号
 */
int JosephusProblem(const int n, const int m) {

    if (n <= 0 || m <= 0) {
        return 0;
    }

    bool p[n + 1];  //人映射到数组（序号对应下标，从下标1到n），true活，false死
    for (int i = 0; i < n + 1; ++i) {   //开始所有人都活
        p[i] = true;
    }

    int i = 1;      //遍历数组的下标，初始第一个人
    int num = 0;      //当前报数值，初始未开始报数
    int last = 1;   //最后死的人的序号（下标），初始第一个人
    int dead = 0;   //当前死亡人数，初始还没人死

    while (dead < n) {  //没死完继续死
        if (i > n) {    //下标溢出从头开始
            i = 1;
        }
        if (p[i]) {             //这人没死
            num++;              //就得报数
            if (num == m) {      //报到该死的数立马去死
                p[i] = false;   //他死了
                num = 0;          //报数值清零
                last = i;       //记录最后死的人是他
                dead++;         //死亡人数加一
            }
        }
        i++;        //下一个人
    }

    return last;    //返回最后死的人的序号
}

void testJosephusProblem() {
    for (int i = 1; i < 10; ++i) {
        int n = rand() % 50;
        int m = rand() % 50;
        printf("%3d,%3d : %3d\n", n, m, JosephusProblem(n, m));
    }
    printf("%3d,%3d : %3d\n", 8, 3, JosephusProblem(8, 3));
}

/*
 * 43、【题目】反向输出链表
 */
typedef struct Node {
    int data;
    struct LNode *next;
} LNode, *LinkList;

/**
 * 反向输出链表
 * @param p 链表首节点（非头结点）指针
 */
void reversePrintLinkedList(const LinkList const p) {
    if (!p) {
        return;
    }
    if (p->next) {
        reversePrintLinkedList(p->next);
    }
    printf("%d ", p->data);
}

/**
 * 创建链表
 * @param h 指向链表头指针的指针
 */
void createLinkedList(LinkList *const h) {
    if (!h) {
        return;
    }
    *h = (LinkList) malloc(sizeof(LNode));
    LinkList r, temp;
    (*h)->next = NULL;
    r = (*h);
    printf("原始链表：");
    for (int i = 0; i < 10; ++i) {
        temp = (LinkList) malloc(sizeof(LNode));
        temp->data = rand() % 100;
        temp->next = NULL;
        r->next = temp;
        r = temp;
        printf("%d ", temp->data);
    }
    printf("\n");
}

void testReversePrintLinkedList() {

    LinkList head;
    createLinkedList(&head);
    printf("链表逆序：");
    reversePrintLinkedList(head->next);
}

/*
 * 44、【题目】连接两个链表
 */
/**
 * 连接两个链表（将h2连接到h1后）
 * @param h1 链表头指针
 * @param h2 链表头指针
 */
void connectLinkedList(const LinkList const h1, const LinkList const h2) {

    if (!h1) {
        return;
    }

    LinkList p = h1;
    while (p->next) {
        p = p->next;
    }
    p->next = h2->next;
}

/**
 * 输出单链表
 * @param h 链表头指针
 */
void printLinkedList(const LinkList const h) {
    if (!h) {
        return;
    }

    LinkList p = h->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
}

void testConnectLinkedList() {

    LinkList h1, h2;
    createLinkedList(&h1);
    createLinkedList(&h2);
    printf("\n链表连接：");
    connectLinkedList(h1, h2);
    printLinkedList(h1);
}

/*
 * 45、【题目】函数指针
 * 输入n为偶数时，调用函数求1/2+1/4+...+1/n,当输入n为奇数时，调用函数1/1+1/3+...+1/n(利用指针函数)
 */
double calcOdd(int n) {
    double sum = 0.0;
    for (int i = 2; i <= n; i += 2) {
        sum += 1.0 / i;
    }
    return sum;
}

double calcEven(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; i += 2) {
        sum += 1.0 / i;
    }
    return sum;
}

void calcOEFractionSum(int n) {
    double (*f)();
    if (n % 2) {
        f = calcEven;
    } else {
        f = calcOdd;
    }
    printf("%f\n", (*f)(n));
}

void testCalcOEFractionSum() {
    for (int i = 1; i < 10; ++i) {
        printf("%d : ", i);
        calcOEFractionSum(i);
    }
}

/*
 * 46、【题目】字符串排序
 */
/**
 * 字符串排序（按照ANSII码序）
 * @param str 字符串数组
 * @param n 字符串个数
 */
void sortStr(const char *str[], const int n) {

    for (int i = 1; i < n; ++i) {   //冒泡思想
        bool flag = true;
        for (int j = 0; j < n - i; ++j) {
            if (strcmp(str[j], str[j + 1]) > 0) {
                char *temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
                flag = false;
            }
        }
        if (flag) {
            return;
        }
    }
}

/**
 * 输出字符串数组
 * @param str 字符串数组
 * @param n 字符串个数
 */
void printStrArr(const char *const str[], const int n) {
    for (int i = 0; i < n; ++i) {
        printf("\"");
        printf("%s\"\n", str[i]);
    }
    printf("\n");
}

void testSortStr() {

    char *str[] = {
            "abcde",
            "abcd",
            "adcd",
            "djhjgfhj",
            "fdfd",
            "andjfkjfd",
            "fhohe",
            ""
    };
    int n = 8;
    printStrArr(str, n);
    sortStr(str, n);
    printStrArr(str, n);
}

/*
 * 47、【题目】猴子分桃
 * 海滩上有一堆桃子，五只猴子来分。
 * 第一只猴子把这堆桃子平均分为五份，多了一个，这只猴子把多的一个扔入海中，拿走了一份。
 * 第二只猴子把剩下的桃子又平均分成五份，又多了一个，它同样把多的一个扔入海中，拿走了一份。
 * 第三、第四、第五只猴子都是这样做的，问海滩上原来最少有多少个桃子？
 */
/**
 * 猴子分桃,最少有多少个桃子(推导公式计算)
 * @param n 猴子数目
 * @param m 分的份数
 */
void monkeyDividePeach(const int n, const int m) {

    long double a = pow(m, n);
    long double b = pow(m - 1, n - 1);
    for (int i = 1; i < INT32_MAX; ++i) {
        long double c = a * (i + 1), temp;
        if (fmodl(c, b) == 0 && (temp = c / b - m + 1) > 0) {
            printf("%.0Lf\n", temp);
            break;
        }
    }
}

void testMonkeyDividePeach() {
    //monkeyDividePeach(12, 8);
    monkeyDividePeach(5, 5);
    //for (int i = 0; i < 10; ++i) {
    //    int n=rand()%10+1;
    //    int m=rand()%10+2;
    //    printf("\n%d,%d:\n",n,m);
    //    monkeyDividePeach(n,m);
    //}
}

/**
 * 猴子分桃，最少有多少个桃子（递归筛选数值）
 * @param num 判断该数值是否成立
 * @param n 猴子数目
 * @param m 份数
 * @return bool型：是true，否false
 */
bool monkeyDividePeach2(const int num, const int n, const int m) {
    if (n == 0) {
        return true;
    } else if (num % m != 1) {  //不能继续满足条件
        return false;
    } else {    //满足条件
        return monkeyDividePeach2(num - num / m - 1, n - 1, m);
    }
}

void testMonkeyDividePeach2() {

    for (int i = 1; i < INT32_MAX; ++i) {
        if (monkeyDividePeach2(i, 5, 5)) {
            printf("%d\n", i);
            break;
        }
    }
    //for (int i = 0; i < 10; ++i) {
    //    int n=rand()%10+1;
    //    int m=rand()%10+2;
    //    for (int i = 1; i < INT32_MAX; ++i) {
    //        if (monkeyDividePeach2(i,n,m)){
    //            printf("\n%d,%d:\n",n,m);
    //            printf("%d\n",i);
    //            break;
    //        }
    //    }
    //}
}

//TODO 需要理解
/**
 * 五猴分桃，最少桃数
 */
void monkeyDividePeach3() {

    int i = 0;  //循环次数
    int j = 1;  //第五只猴子分的桃子
    int x;      //桃子数
    while (i < 5) {
        x = 4 * j;
        for (i = 0; i < 5;) {
            if (x % 4 != 0) {   //必须连续五次x都能被4整除才符合条件.
                break;
            } else {
                x = (x / 4) * 5 + 1;
                i++;
            }
        }
        j++;
    }

    printf("最少有 %d 个", x);
}

void testMonkeyDividePeach3() {
    monkeyDividePeach3();
}

/*
 * 48、【题目】求两位数
 * 809*??=800*??+9*??
 * 其中??代表两位数。
 * 809*??结果为四位数，8*??结果为两位数，9*??结果为3位数。
 * 求??代表的两位数，及809*??后的结果？
 */
/**
 * 求满足条件的两位数
 * @return 满足要求的两位数
 */
int findDoubleDigit() {

    for (int i = 10; i < 100; ++i) {
        int a = 809 * i;
        int b = 8 * i;
        int c = 9 * i;
        if (a > 999 & a < 10000 && b > 9 && b < 100 && c > 99 && c < 1000 && a == b * 100 + c) {
            return i;
        }
    }
}

void testFindDoubleDigit() {
    int x = findDoubleDigit();
    printf("809*%d=800*%d+9*%d", x, x, x);
}

/*
 * 49、【题目】整数进制转换
 */
/**
 * 其他进制整数转十进制整数
 * @param str 其他进制数值（字符串形式,不要带前缀0或0x）
 * @param base 目标进制
 * @return 对应十进制数
 */
long long otherToDecimal(const char *str, const int base) {

    int len = strlen(str);
    long long sum = 0LL;
    for (int i = len - 1; i >= 0; --i) {    //加权求和
        if (isdigit(str[i])) {
            sum += (str[i] - '0') * (long long) pow(base, len - 1 - i);
        } else if (isalpha(str[i])) {
            sum += (tolower(str[i]) - 'a' + 10) * (long long) pow(base, len - 1 - i);
        }
    }
    return sum;
}

void testOtherToDecimal() {
    printf("b%s: %lld\n", "1001001", otherToDecimal("1001001", 2));
    printf("0%s: %lld\n", "16", otherToDecimal("16", 8));
    printf("0x%s: %lld\n", "ffff", otherToDecimal("ffff", 16));
}

/**
 * 十进制整数转其他进制整数
 * @param x 十进制数值
 * @param base 目标进制
 * @return 对应的指定进制数值（不带前缀0或0x）
 */
char *decimalToOther(const int x, const int base) {
    char *result = (char *) malloc(sizeof(char) * 1024);
    int t = x, i = 0;
    while (t) {     //除基取余
        int m = t % base;
        if (m >= 0 && m <= 9) {
            result[i++] = m + '0';
        } else if (m >= 10 && m <= 35) {
            result[i++] = m - 10 + 'a';
        }
        t /= base;
    }
    result[i] = '\0';

    for (int j = 0; j < i / 2; ++j) {   //翻转
        int temp = result[j];
        result[j] = result[i - 1 - j];
        result[i - 1 - j] = temp;
    }
    return result;
}

void testDecimalToOther() {
    char *s = decimalToOther(10, 2);
    printf("%d: b%s\n", 10, s);
    s = decimalToOther(10, 8);
    printf("%d: 0%s\n", 10, s);
    s = decimalToOther(10, 16);
    printf("%d: 0x%s\n", 10, s);
    free(s);
}

/*
 * 50、【题目】一个偶数总能表示为两个素数之和
 */
/**
 * 一偶数分解为两素数和
 * @param x 待分解偶数
 */
void resolveEvenTwoPrime(const int x) {

    if (x <= 2) {
        printf("error!\n");
    }
    for (int i = 2; i <= x / 2; ++i) {
        if (isPrime(i) && isPrime(x - i)) {
            printf("%d+%d=%d\n", i, x - i, x);
            break;
        }
    }
}

void testResolveEvenTwoPrime() {
    for (int i = 2; i <= 100; i += 2) {
        resolveEvenTwoPrime(i);
    }
}

/*
 * 51、【题目】连接两个字符串
 */
/**
 * 连接两个字符串
 * @param target 目标字符串
 * @param source 源字符串
 * @return 连接后的字符串
 */
char *connectStr(char *target, const char *source) {
    if (!target || !source) {
        return target;
    }

    int lenT = strlen(target), lenS = strlen(source);
    char *temp = (char *) malloc(sizeof(char) * (lenT + lenS + 1));
    for (int i = 0; i < lenT; ++i) {
        temp[i] = target[i];
    }
    for (int i = 0; i <= lenS; ++i) {
        temp[lenT + i] = source[i];
    }
    target = temp;    //修改原目标字符串

    return target;
}

void testConnectStr() {
    char t[1024] = "abcd";
    char *s = "efg";
    puts(connectStr(t, s));
}

/*
 * 52、【题目】加密电话
 * 某个公司采用公用电话传递数据，数据是四位的整数，在传递过程中是加密的，加密规则如下：
 * 每位数字都加上5,然后用和除以10的余数代替该数字，再将第一位和第四位交换，第二位和第三位交换。
 */
void encryptTelegram(int data) {
    int result[5] = {0};
    int i = 0;
    while (data) {
        result[i++] = (data % 10 + 5) % 10;
        data /= 10;
    }

    for (int j = 0; j < i; ++j) {
        printf("%d", result[j]);
    }
    printf("\n");
}

void testEncryptTelegram() {
    for (int i = 1000; i < 1100; ++i) {
        printf("%d: ", i);
        encryptTelegram(i);
    }
    printf("%d: ", 1234);
    encryptTelegram(1234);
}

/*
 * 53、【题目】时间函数使用
 */
void testTime() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("当前本地时间为: %s", asctime(timeinfo));
}

/*
 * 54、【题目】猜数游戏
 */
/**
 * 猜数字游戏
 */
void guessNumber() {
    int n;
    char begin;
    int count = 1;
    srand((int) time(NULL));
    int m = (rand() % 100) + 1;
    puts("游戏开始，请输入数字:");
    while (1) {
        scanf("%d", &n);
        if (n == m) {
            printf("猜中了，使用了 %d 次！\n", count);
            if (count == 1) {
                printf("你是神级人物了！膜拜\n");
                getchar();
                printf("你已经达到最高级别，还需要玩吗？Y/N \n");
                scanf("%c", &begin);
                if (begin == 'Y' || begin == 'y')      //重复玩的一个嵌套循环
                {
                    guessNumber();
                } else {
                    printf("谢谢，再见!\n");
                }
            } else if (count <= 5) {
                printf("你是王级人物了！非常赞\n");
                getchar();
                printf("需要挑战最高级别不？Y/N \n");
                scanf("%c", &begin);
                if (begin == 'Y' || begin == 'y') {
                    guessNumber();
                } else {
                    printf("谢谢，再见!\n");
                }
            } else if (count <= 10) {
                printf("你是大师级人物了！狂赞\n");
                getchar();
                printf("需要挑战最高级别不？Y/N \n");
                scanf("%c", &begin);
                if (begin == 'Y' || begin == 'y') {
                    guessNumber();
                } else {
                    printf("谢谢，再见!\n");
                }
            } else if (count <= 15) {
                printf("你是钻石级人物了！怒赞\n");
                getchar();
                printf("需要挑战最高级别不？Y/N \n");
                scanf("%c", &begin);
                if (begin == 'Y' || begin == 'y') {
                    guessNumber();
                } else {
                    printf("谢谢，再见!\n");
                }
            } else {
                getchar();
                printf("你的技术还有待提高哦！重玩？ Y/N\n");
                scanf("%c", &begin);
                if (begin == 'Y' || begin == 'y') {
                    guessNumber();
                } else {
                    printf("谢谢，再见!\n");
                }
            }
            break;
        } else if (n < m) {
            puts("太小了!");
            puts("重新输入:");
        } else {
            puts("太大了!");
            puts("重新输入:");
        }
        count++;//计数器
    }
}


/*
 * 55、【题目】计算字符串中子串出现的次数
 */
/**
 * 计算字符串中子串出现的次数
 * @param str 目标字符串
 * @param substr 子串
 * @return 次数
 */
int substrTimes(const char *str, const char *substr) {
    int count = 0;
    int lenS = strlen(str), lenSub = strlen(substr);
    for (int i = 0; i <= lenS - lenSub; ++i) {
        if (str[i] == substr[0]) {
            int j = 1;
            while (j < lenSub && str[i + j] == substr[j]) {
                j++;
            }
            if (j == lenSub) {
                count++;
            }
        }
    }
    return count;
}

void testSubstrTimes() {
    printf("%s contain %s: %d\n", "aaaa", "a", substrTimes("aaaa", "a"));
    printf("%s contain %s: %d\n", "aaaa", "aa", substrTimes("aaaa", "aa"));
    printf("%s contain %s: %d\n", "aaaa", "aaa", substrTimes("aaaa", "aaa"));
    printf("%s contain %s: %d\n", "aaaa", "aaaa", substrTimes("aaaa", "aaaa"));
    printf("%s contain %s: %d\n", "abaa", "ab", substrTimes("abaa", "ab"));
    printf("%s contain %s: %d\n", "abababa", "a", substrTimes("abababa", "aba"));
    printf("%s contain %s: %d\n", "abababa", "ab", substrTimes("abababa", "ab"));
    printf("%s contain %s: %d\n", "abababa", "t", substrTimes("abababa", "t"));
}

/*
 * 56、【题目】结构体信息保存到文件
 */
typedef struct {
    int ID;
    int math;
    int English;
    int C;
    int avargrade;
    char name[20];
} Stu;

/**
 * 结构体信息保存到文件
 */
void testWriteFile() {
    FILE *fp;
    Stu stu[3];
    int i, avargrade = 0;
    printf("请输入3个同学的信息：学生号，姓名，3门成绩:\n");
    for (i = 0; i < 3; i++) {
        scanf("%d %s %d %d %d", &(stu[i].ID), stu[i].name, &(stu[i].math), &(stu[i].English), &(stu[i].C));
        stu[i].avargrade = (stu[i].math + stu[i].English + stu[i].C) / 3;
    }

    if ((fp = fopen("stud.txt", "w")) == NULL) {
        printf("error :cannot open file!\n");
        exit(0);
    }
    for (i = 0; i < 3; i++)
        fprintf(fp, "%d %s %d %d %d %d\n", stu[i].ID, stu[i].name, stu[i].math, stu[i].English, stu[i].C,
                stu[i].avargrade);

    fclose(fp);
}


int main() {

    srand((unsigned) time(NULL));

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
    testPrimeFactors();
    //testPerfectNumber();
    //testFindPerfectNumber();
    //testGCDLCM();
    //testGcdAndLcm();
    //testSortThreeNumber();
    //testGetBonus();
    //testDayOfYear();
    //testNotRepeatThreeDigitsSimple();
    //testNotRepeatThreeDigits();
    //testPrintMultiplicationTable();
    // testPrintRhombus();
    //testPrintChessBoard();
    //testCalcCountOfStr();
    //testFractionSum();
    //testFactorial();
    //testFactorialLoop();
    //testIsPalindrome();
    //testSameNumberSum();
    //testPrimeHundred();
    //testPrintReverseArr();
    //testReverseArr();
    //testInsertArr();
    //testStaticFun();
    //testAutoFun();
    //testExternFun();
    //testRegisterFun();
    //testDefineFun();
    //testFactorialSum();
    //testTemperatureTrans();
    //testSaveInterests();
    //testIsLeapYear();
    //testPrintYHTriangle();
    //testPrintYHTriangle2();
    //testIsPerfectSquare();
    //testCalcOnePerfectSquare();
    //testPingPangGame();
    //testResolveInt();
    //testDayOfTheWeek();
    //testDeleteChar();
    //testSortTenNumber();
    //testMinMaxSwitch();
    //testLoopMoveArr();
    //testJosephusProblem();
    //testReversePrintLinkedList();
    //testConnectLinkedList();
    //testCalcOEFractionSum();
    //testSortStr();
    //testMonkeyDividePeach();
    //testMonkeyDividePeach2();
    //testMonkeyDividePeach3();
    //testFindDoubleDigit();
    //testOtherToDecimal();
    //testDecimalToOther();
    //testResolveEvenTwoPrime();
    //testConnectStr();
    //testEncryptTelegram();
    //testTime();
    //guessNumber();
    //testSubstrTimes();
    // testWriteFile();


    printf("\n运行耗时：");
    gettimeofday(&end, 0);
    double timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;    //微秒数
    timeuse /= 1000; //除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时
    printf("%f ms", timeuse);

    return 0;
}
