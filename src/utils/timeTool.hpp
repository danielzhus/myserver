#include<chrono>
using namespace std;
using namespace std::chrono;

// 来自csdn oncealong的代码
// 使用方法
// 构造一个对象自动会赋值
// 调用其中的函数会得到差值
class Timer
{
	public:
		Timer() : m_begin(high_resolution_clock::now()) {}
		void reset() { m_begin = high_resolution_clock::now(); }
		//默认输出毫秒
		int64_t elapsed() const
		{
			return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
		}
		//微秒
		int64_t elapsed_micro() const
		{
			return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
		} 
		//纳秒
		int64_t elapsed_nano() const
		{
			return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
		}
		//秒
		int64_t elapsed_seconds() const
		{
			return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
		}
		//分
		int64_t elapsed_minutes() const
		{
			return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
		}
		//时
		int64_t elapsed_hours() const
		{
			return duration_cast<chrono::hours>(high_resolution_clock::now() - m_begin).count();
		}
	private:
		time_point<high_resolution_clock> m_begin;
};
