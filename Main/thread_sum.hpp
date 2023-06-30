#include<iostream>
#include<vector>
#include<thread>

struct sum_obj {
    int start, end;
    int sum;
    sum_obj():start(0), end(0), sum(0) {}
};

void sum_thread(sum_obj& param) {
    param.sum = 0;
    for(int i = param.start; i < param.end; ++i) {
        param.sum += i;
    }
    printf("thtread id: %d \n", std::this_thread::get_id());
    printf("sum(%d : %d)= %d \n", param.start, param.end, param.sum);
}

void test_sum_thread() {
    int N = 1000;
    int core_num = std::thread::hardware_concurrency();
    int thread_num = core_num * 2;
    std::vector<sum_obj> sum_objs(thread_num);
    std::vector<std::thread> sum_threads(thread_num);
    int step = (N + thread_num - 1) / thread_num;
    for(int i  = 0; i < thread_num; i++) {
        sum_objs[i].start = i * step + 1;
        sum_objs[i].end = (i+1) * step + 1;
        if(sum_objs[i].end > (N+1) ) {
            sum_objs[i].end = (N+1);
        }
        sum_threads[i] = std::thread(sum_thread, std::ref(sum_objs[i]));
    }

    for(auto& th:sum_threads) {
        th.join();
    }
    long sum = 0;
    for(auto& p : sum_objs) {
        sum += p.sum;
    }
    printf("1+2+...+ %d = %d \n", N, sum);

}



