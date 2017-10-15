/*http://blog.csdn.net/dengxu11/article/details/7311820*/

/*C语言实现 vector( 动态数组) 改进版
标签： vector语言cinsertfileinclude
2012-03-02 12:54 8295人阅读 评论(19) 收藏 举报
分类：
C语言（31）

版权声明：本文为博主原创文章，未经博主允许不得转载。

之所以再写一封邮件缘起于我写的《 C语言实现 vector( 动态数组)》这篇文章http://blog.csdn.net/dengxu11/article/details/5915857。

        原来这个是在Linux下写的，多谢troublema的提议，我发现那份代码在windows上存在一些问题，故做了改进，以求在widnows上和Linux上都是OK的。

另外非常感谢troublema，没有他我发现不了这个存在的问题。*/


    #include "cvector.h"  
      
    int main()  
    {  
        int i = 1;  
        cvector cv = cvector_create(sizeof(int));  
        cvector_pushback(cv, &i);  
        cvector_pushback(cv, &i);  
        cvector_pushback(cv, &i);  
        cvector_pushback(cv, &i);  
        cv_print(cv);  
        cvector_destroy(cv);  
        return 0;  
    }  
