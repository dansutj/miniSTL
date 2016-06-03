#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <cstdlib>


namespace miniSTL
{
	/*
	 * 空间适配器, 以字节数为单位分配
	 * 内部使用
	 */
	class alloc{
	private:
		enum EAlign { ALIGN = 8 }; //小区块的上调边界
		enum EMaxBytes { MAXBYTES = 128 }; //小区块的上限 超过的区块由malloc分配
		enum ENFreeLists { NFREELISTS = (EMaxBytes::MAXBYTES / EAlign::ALIGN) }; //free list个数
		enum ENObjs { NOBJS = 20 }; //每次分配的节点数

		//free lists的节点构造
		union obj{
			union obj* next;
			char client[1];
        };

		//内存池
		static obj* free_list[ENFreeLists::NFREELISTS];
		
		static char* start_free; //后备池的起始位置
		static char* end_free; //后备池的结束位置
		static size_t heap_size;


		//将bytes上调至8的倍数
		static size_t ROUND_UP(size_t bytes){
			return (((bytes) + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
		}

		//根据区块的大小, 决定使用第n号free list, n从0开始计算
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes)+EAlign::ALIGN - 1) / EAlign::ALIGN - 1);
		}

		//返回一个大小为n的对象, 并可能加入到大小为n的其他区块的free list中
		static void* refill(size_t n);

		//配置一大块空间, 可以容纳nobjs个大小为size的区块
		//如果配置nobjs个区块有所不便, njobs的范围在1～20之间
		static char* chunk_alloc(size_t size, size_t& nobjs);
	
	public:
		static void* allocate(size_t bytes);
		static void deallocate(void* ptr, size_t bytes);
		static void* reallocate(void* ptr, size_t old_size, size_t new_size);
	};
}

#endif