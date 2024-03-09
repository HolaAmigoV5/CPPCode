#include <iostream>		// #表示预处理(preprocessor)指令，发生在真正编译之前
//#include "Log.h"		// include预处理指令：复制include的文件到当前文件里
#include "Main.h"
#include "LogClass.h"
#include "Log.h"	// 链接Common/log头文件

/* 
* << 表示操作符(Operator)，可以被重载，本质是个函数(function)
* windows编译器中，cpp文件先被【编译器】编译成obj文件，然后被【链接器】链接到可执行(exe)文件中
* 编译器：负责把cpp文件编译成obj文件
* 链接器：负责把所有obj文件拿过来，然后把它们联系起来
*/

/*
* 这里设置成static，表示Multiply只在当前文件（Main.cpp）中使用，
* 在下面Main()方法中不调用Multiply()方法，链接器就不会链接Log()方法
* 否则会链接Log方法。
*/
// static int Multiply(int a, int b) {
//	Log("wby");
//	return a * b;
//}

 // 演示：LNK1169: 找到一个或多个多重定义的符号
 // void Log(const char* message) {
	// std::cout << message << std::endl;
 //}



// main() 为入口函数，可以在项目属性中进行修改
int main() {
	//std::cout << Multiply(4, 5) << std::endl;

	// 变量
	//std::cout << "****************************变量************************" << std::endl;
	//Variables();

	//std::cout << "***************************循环*************************" << std::endl;
	//Loops();

	//std::cout << "***********************指针和引用*************************" << std::endl;
	//PointerAndRefrence();

	//std::cout << "***********************类*************************" << std::endl;
	//CallClassDemo();

	/*LogClass log;
	log.SetLevel(Level::Levelinfo);
	log.Warn("Hello!");
	log.Error("Hello!");
	log.Info("Hello!");*/

	// 静态类
	//CallStaticDemo();

	// 局部静态
	//CallLocalStaticFunctionDemo();
	//CallLocalStaticSingletonDemo();

	// 构造函数
	//CallConstructorDemo();

	// 继承
	//CallInheritanceDemo();

	// 虚函数
	//VirtualFunctionDemo();

	// 数组
	//ArraysDemo();

	// 字符串
	//StringsDemo();

	//常量
	//ConstDemo();

	// Mutable
	//MutableDemo();

	// 成员初始化列表
	//MemberListsDemo();

	// 操作符
	//OperatorDemo();

	// 智能指针
	//SmartPointerDemo();


	// 复制和拷贝构造函数
	//CopyConstructors();

	// 箭头操作符重载
	//ArrowEntityDemo();

	// 动态数组Vector
	//VectorDemo();

	// 动态数组优化
	//OptmizeVectorDemo();

	// 调用别的项目中的Log
	// Common::Log log;
	// log.SetLevel(Common::Level::Levelinfo);
	// log.Error("出错了！");

	//std::cout << "***********************模板*************************" << std::endl;
	//TemplateDemo();

	// 宏
	//MacrosDemo();

	// 静态数组
	//ArrayDemo();

	// 函数指针
	//FunctionPointers();

	// Lambda 表达式
	//LambdaDemo();

	// 线程
	//ThreadDemo();

	//计时
	//TimingDemo();

	//排序
	//SortingDemo();


	// 类型双关
	//TypePunningDemo();

	// 联合体
	//UnionDemo();

	// 动态转换
	//DynamicCastDemo();

	// 基准测试
	//BenchmarkingDemo();

	// 机构化绑定
	//StructuredBindingDemo();


	//OptionalMain();


	// string 优化加速
	//StringFastDemo();

	// 数据可视化
	//VisualBenchmarking();

	// 参数调用顺序
	//ArgumentEvOrder();

	// move 移动
	//MoveDemo();

	// DIY Array
	//DIYArrayDemo();

	// DIY Vector
	//DIYVectorDemo();

	// 迭代器
	IteratorDemo();

	std::cin.get();
}

#if 0	// 0表示被禁用的代码, 1表示启用的代码
void PrintToConsole() {

}
#endif // 



