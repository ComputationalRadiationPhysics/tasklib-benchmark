#include <chrono>
#include <sg/superglue.hpp>

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "sg/superglue.hpp"
#include "common.h"

using namespace std::chrono;

struct Options : public DefaultOptions<Options> {};

struct MyTask0 : Task<Options, 0> {
    MyTask0()
    {
    }

    void run()
    {
        sleep( task_duration );
    }
};

struct MyTask1 : Task<Options, 1> {
    unsigned task_id;
    uint64_t & data1;

    MyTask1(unsigned task_id, Handle<Options> & h1, uint64_t & data1)
        : task_id(task_id)
        , data1(data1)
    {
        register_access(ReadWriteAdd::write, h1);
    }

    void run()
    {
        sleep( task_duration );
        data1 = hash(data1 + task_id);
    }
};

struct MyTask2 : Task<Options, 2> {
    unsigned task_id;
    uint64_t & data1;
    uint64_t & data2;

    MyTask2(unsigned task_id,
            Handle<Options> & h1, uint64_t & data1,
            Handle<Options> & h2, uint64_t & data2)
        : task_id(task_id)
        , data1(data1)
        , data2(data2)
    {
        register_access(ReadWriteAdd::write, h1);
        register_access(ReadWriteAdd::write, h2);
    }

    void run()
    {
        sleep( task_duration );
        data1 = hash(data1 + task_id);
        data2 = hash(data2 + task_id);
    }
};

struct MyTask3 : Task<Options, 3> {
    unsigned task_id;
    uint64_t & data1;
    uint64_t & data2;
    uint64_t & data3;

    MyTask3(unsigned task_id,
            Handle<Options> & h1, uint64_t & data1,
            Handle<Options> & h2, uint64_t & data2,
            Handle<Options> & h3, uint64_t & data3)
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
        sleep( task_duration );
        data1 = hash(data1 + task_id);
        data2 = hash(data2 + task_id);
        data3 = hash(data3 + task_id);
    }
};

struct MyTask4 : Task<Options, 4> {
    unsigned task_id;
    uint64_t & data1;
    uint64_t & data2;
    uint64_t & data3;
    uint64_t & data4;

    MyTask4(unsigned task_id,
            Handle<Options> & h1, uint64_t & data1,
            Handle<Options> & h2, uint64_t & data2,
            Handle<Options> & h3, uint64_t & data3,
            Handle<Options> & h4, uint64_t & data4
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
        sleep( task_duration );
        data1 = hash(data1 + task_id);
        data2 = hash(data2 + task_id);
        data3 = hash(data3 + task_id);
        data4 = hash(data4 + task_id);
    }
};

struct MyTask5 : Task<Options, 5> {
    unsigned task_id;
    uint64_t & data1;
    uint64_t & data2;
    uint64_t & data3;
    uint64_t & data4;
    uint64_t & data5;

    MyTask5(unsigned task_id,
            Handle<Options> & h1, uint64_t & data1,
            Handle<Options> & h2, uint64_t & data2,
            Handle<Options> & h3, uint64_t & data3,
            Handle<Options> & h4, uint64_t & data4,
            Handle<Options> & h5, uint64_t & data5
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
        sleep( task_duration );
        data1 = hash(data1 + task_id);
        data2 = hash(data2 + task_id);
        data3 = hash(data3 + task_id);
        data4 = hash(data4 + task_id);
        data5 = hash(data5 + task_id);
    }
};

int main(int argc, char* argv[])
{
    read_args(argc, argv);
    generate_access_pattern();

    SuperGlue<Options> tm( n_threads );
    std::vector< uint64_t > data( n_resources );
    std::vector< Handle<Options> > resources( n_resources );

    auto start = high_resolution_clock::now();
 
    for( unsigned i = 0; i < n_tasks; ++i )
        switch( access_pattern[i].size() )
        {
        case 0:
            tm.submit( new MyTask0() );
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

    tm.barrier();
    auto end = high_resolution_clock::now();

    std::cout << "total " << duration_cast<microseconds>(end-start).count() << " μs" << std::endl;

    for(int i = 0; i < n_resources; ++i)
        if(data[i] != expected_hash[i])
        {
            std::cout << "error: invalid result!" << std::endl;
            return 1;
        }

    std::cout << "success" << std::endl;

    return 0;
}

