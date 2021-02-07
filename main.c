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
 * 因数学家莱昂纳多·斐波那契（Leonardoda Fibonacci）以兔子繁殖为例子而引入，故又称为“兔子数列”。
 * 有一对兔子，从出生后第3个月起每个月都生一对兔子，小兔子长到第三个月后每个月又生一对兔子，
 * 假如兔子都不死，问每个月的兔子总数为多少？
 * 兔子的规律为数列：0、1、1、2、3、5、8、13、21、34、........。
*/
/**
 * 计算斐波那契数列中的值
 * @param n 数列中的位序
 * @return 数列中的第n个值
 */
long long fibonacci(int n) {
    if (n <= 0 || n > 93) { //第93个数值long long会溢出
        return NAN;
    }

    //static减少非必要的重复计算（重复查询时），只依次往后计算到目标值，并保存已经计算出的值
    static long long result[100] = {0L, 1L, 1L};
    static int i = 3;
    for (; i < n; ++i) {
        //a[n]=a[n-1]+a[n-2]
        result[i] = result[i - 1] + result[i - 2];
    }

    return result[n - 1];
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
 * @param n 吃到只剩一个桃子需要的天数
 * @return 开始的桃子数
 */
int monkeyEatPeach(int n){

    if (n<=1){
        return 1;
    } else{
        //a[n-1]=a[n]/2-1   ==>     a[n]=(a[n-1]+1)*2
        return (monkeyEatPeach(n-1)+1)*2;
    }
}

void testMonkeyEatPeach(){
    for (int i = 1; i <= 10; ++i) {
        printf("%d\n",monkeyEatPeach(i));
    }
}



int main() {

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
    testMonkeyEatPeach();

    gettimeofday(&end, 0);
    double timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;    //微秒数
    timeuse /= 1000; //除以1000则进行毫秒计时，如果除以1000000则进行秒级别计时，如果除以1则进行微妙级别计时
    printf("%f ms", timeuse);

    return 0;
}
