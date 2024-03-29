#include <chrono>
#include <sg/superglue.hpp>
#include <atomic>
#include <iomanip>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <condition_variable>
#include <thread>
#include <mutex>
#include "sg/superglue.hpp"
#include "common.h"

using namespace std::chrono;

struct Options : public DefaultOptions<Options> {};

struct MyTask0 : Task<Options, 0> {
    unsigned task_id;

    MyTask0(unsigned task_id)
        : task_id(task_id)
    {
    }

    void run()
    {
        task_begin[task_id] = steady_clock::now();
        sleep(task_duration[task_id]);
        task_thread[task_id] = std::this_thread::get_id();
        task_end[task_id] = steady_clock::now();
    }
};

struct MyTask1 : Task<Options, 1> {
    unsigned task_id;
    std::array<uint64_t, 8> & data1;

    MyTask1(unsigned task_id, Handle<Options> & h1, std::array<uint64_t, 8> & data1)
        : task_id(task_id)
        , data1(data1)
    {
        register_access(ReadWriteAdd::write, h1);
    }

    void run()
    {
        task_begin[task_id] = steady_clock::now();

        sleep(task_duration[task_id]);
        task_thread[task_id] = std::this_thread::get_id();
        hash(task_id, data1);

        task_end[task_id] = steady_clock::now();
    }
};

struct MyTask2 : Task<Options, 2> {
    unsigned task_id;
    std::array<uint64_t, 8> & data1;
    std::array<uint64_t, 8> & data2;

    MyTask2(unsigned task_id,
            Handle<Options> & h1, std::array<uint64_t, 8> & data1,
            Handle<Options> & h2, std::array<uint64_t, 8> & data2)
        : task_id(task_id)
        , data1(data1)
        , data2(data2)
    {
        register_access(ReadWriteAdd::write, h1);
        register_access(ReadWriteAdd::write, h2);
    }

    void run()
    {
        task_begin[task_id] = steady_clock::now();

        sleep(task_duration[task_id]);
        task_thread[task_id] = std::this_thread::get_id();
        hash(task_id, data1);
        hash(task_id, data2);

        task_end[task_id] = steady_clock::now();
    }
};

struct MyTask3 : Task<Options, 3> {
    unsigned task_id;
    std::array<uint64_t, 8> & data1;
    std::array<uint64_t, 8> & data2;
    std::array<uint64_t, 8> & data3;

    MyTask3(unsigned task_id,
            Handle<Options> & h1, std::array<uint64_t, 8> & data1,
            Handle<Options> & h2, std::array<uint64_t, 8> & data2,
            Handle<Options> & h3, std::array<uint64_t, 8> & data3)
        : task_id(task_id)
        , data1(data1)
        , data2(data2)
        , data3(data3)
    {
        register_access(ReadWriteAdd::write, h1);
        register_access(ReadWriteAdd::write, h2);
        register_access(ReadWriteAdd::write, h3);
    }

    void run()
    {
        task_begin[task_id] = steady_clock::now();

        sleep(task_duration[task_id]);
        task_thread[task_id] = std::this_thread::get_id();
        hash(task_id, data1);
        hash(task_id, data2);
        hash(task_id, data3);

        task_end[task_id] = steady_clock::now();
    }
};

struct MyTask4 : Task<Options, 4> {
    unsigned task_id;
    std::array<uint64_t, 8> & data1;
    std::array<uint64_t, 8> & data2;
    std::array<uint64_t, 8> & data3;
    std::array<uint64_t, 8> & data4;

    MyTask4(unsigned task_id,
            Handle<Options> & h1, std::array<uint64_t, 8> & data1,
            Handle<Options> & h2, std::array<uint64_t, 8> & data2,
            Handle<Options> & h3, std::array<uint64_t, 8> & data3,
            Handle<Options> & h4, std::array<uint64_t, 8> & data4
            )
        : task_id(task_id)
        , data1(data1)
        , data2(data2)
        , data3(data3)
        , data4(data4)
    {
        register_access(ReadWriteAdd::write, h1);
        register_access(ReadWriteAdd::write, h2);
        register_access(ReadWriteAdd::write, h3);
        register_access(ReadWriteAdd::write, h4);
    }

    void run()
    {
        task_begin[task_id] = steady_clock::now();

        sleep(task_duration[task_id]);
        task_thread[task_id] = std::this_thread::get_id();
        hash(task_id, data1);
        hash(task_id, data2);
        hash(task_id, data3);
        hash(task_id, data4);

        task_end[task_id] = steady_clock::now();
    }
};

struct MyTask5 : Task<Options, 5> {
    unsigned task_id;
    std::array<uint64_t, 8> & data1;
    std::array<uint64_t, 8> & data2;
    std::array<uint64_t, 8> & data3;
    std::array<uint64_t, 8> & data4;
    std::array<uint64_t, 8> & data5;

    MyTask5(unsigned task_id,
            Handle<Options> & h1, std::array<uint64_t, 8> & data1,
            Handle<Options> & h2, std::array<uint64_t, 8> & data2,
            Handle<Options> & h3, std::array<uint64_t, 8> & data3,
            Handle<Options> & h4, std::array<uint64_t, 8> & data4,
            Handle<Options> & h5, std::array<uint64_t, 8> & data5
            )
        : task_id(task_id)
        , data1(data1)
        , data2(data2)
        , data3(data3)
        , data4(data4)
        , data5(data5)
    {
        register_access(ReadWriteAdd::write, h1);
        register_access(ReadWriteAdd::write, h2);
        register_access(ReadWriteAdd::write, h3);
        register_access(ReadWriteAdd::write, h4);
        register_access(ReadWriteAdd::write, h5);
    }

    void run()
    {
        task_begin[task_id] = steady_clock::now();

        sleep(task_duration[task_id]);
        task_thread[task_id] = std::this_thread::get_id();
        hash(task_id, data1);
        hash(task_id, data2);
        hash(task_id, data3);
        hash(task_id, data4);
        hash(task_id, data5);

        task_end[task_id] = steady_clock::now();
    }
};


std::mutex m;
std::condition_variable cv;
volatile bool start_flag = false;
std::atomic_int count(0);

struct BlockingTask : Task<Options, 0> {
    unsigned i;
    BlockingTask(unsigned i)
        : i(i)
    {
        
    }

    void run()
    {
        wait_task_begin[i] = steady_clock::now();
        wait_task_thread[i] = std::this_thread::get_id();

        count.fetch_add(1);
        while( ! start_flag );

        wait_task_end[i] = steady_clock::now();
    }
};

int main(int argc, char* argv[])
{
    read_args(argc, argv);
    generate_access_pattern();

    SuperGlue<Options> tm( n_workers );
    std::vector< std::array<uint64_t, 8> > data( n_resources );
    std::vector< Handle<Options> > resources( n_resources );

    if( block_execution )
    {
        // spawn (n_workers - 1) many tasks to block all threads
        // the main thread is the first worker, so decrement by one
        for( unsigned i = 0; i < n_workers; ++i )
            tm.submit( new BlockingTask(i) );

        // wait until all block-tasks are up and running
        int last_count = count;
        while( count < n_workers-1 ) {
            if(last_count != count )
                std::cout << count << std::endl;

            last_count = count;
        }
    }
    
    auto start = steady_clock::now();
 
    for( unsigned i = 0; i < n_tasks; ++i )
        switch( access_pattern[i].size() )
        {
        case 0:
            tm.submit( new MyTask0(i) );
            break;

        case 1:
            tm.submit( new MyTask1(i, resources[access_pattern[i][0]], data[access_pattern[i][0]]) );
            break;

        case 2:
            tm.submit( new MyTask2(i,
                                   resources[access_pattern[i][0]], data[access_pattern[i][0]],
                                   resources[access_pattern[i][1]], data[access_pattern[i][1]]));
            break;
        case 3:
            tm.submit( new MyTask3(i,
                                   resources[access_pattern[i][0]], data[access_pattern[i][0]],
                                   resources[access_pattern[i][1]], data[access_pattern[i][1]],
                                   resources[access_pattern[i][2]], data[access_pattern[i][2]]));
            break;
        case 4:
            tm.submit( new MyTask4(i,
                                   resources[access_pattern[i][0]], data[access_pattern[i][0]],
                                   resources[access_pattern[i][1]], data[access_pattern[i][1]],
                                   resources[access_pattern[i][2]], data[access_pattern[i][2]],
                                   resources[access_pattern[i][3]], data[access_pattern[i][3]]));
            break;
        case 5:
            tm.submit( new MyTask5(i,
                                   resources[access_pattern[i][0]], data[access_pattern[i][0]],
                                   resources[access_pattern[i][1]], data[access_pattern[i][1]],
                                   resources[access_pattern[i][2]], data[access_pattern[i][2]],
                                   resources[access_pattern[i][3]], data[access_pattern[i][3]],
                                   resources[access_pattern[i][4]], data[access_pattern[i][4]]));
            break;
        }

    auto mid = steady_clock::now();
    
    if( block_execution )
    {
        // trigger execution of tasks
        {
            //std::unique_lock<std::mutex> l(m);
            start_flag = true;
        }
        //cv.notify_all();
    }

    tm.barrier();

    auto end = steady_clock::now();

    for(int i = 0; i < n_resources; ++i)
        if(data[i] != expected_hash[i])
        {
            std::cout << "error: invalid result!" << std::endl;
            return -1;
        }

    std::cout << "success" << std::endl;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "total " << duration_cast<nanoseconds>(end-start).count()/1000.0 << " μs" << std::endl;
    std::cout << "emplacement " << duration_cast<nanoseconds>(mid-start).count()/1000.0 << " μs" << std::endl;
    std::cout << "execution " << duration_cast<nanoseconds>(end-mid).count()/1000.0 << " μs" << std::endl;
    std::cout << "scheduling gap " << duration_cast<nanoseconds>(get_scheduling_gap()).count() / 1000.0 << " μs" << std::endl;

    get_critical_path();
    output_svg(std::ofstream("trace_superglue.svg"));
    return 0;
}

