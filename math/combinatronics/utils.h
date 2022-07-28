#include <map>
#include <cmath>


long long catalan(long long value){
    using namespace std;
    static map<long long, long long> memo{}; 
    if(memo.count(value) == 0){
        long long answer = 1;
        for(double i = 0; i < value; i++){
            answer *= (4.*i+2.)/(i+2.);
        }
    }
    return memo[value];
}

constexpr long long catalan(long long value){
    using namespace std;
    long long answer = 1;
    for(double i = 0; i < value; i++){
        answer *= (4.*i+2.)/(i+2.);
    }
    return answer;
}

long long factorial(long long value){
    long long answer = 1;
    while(value > 1){
        answer *= value;
        value -= 1;
    }
    return answer;
}

long gamma_fac(long value){
    return std::tgamma(value+1);
}

template<class BidirIt>
bool next_permutation(BidirIt first, BidirIt last)
{
  auto r_first = std::make_reverse_iterator(last);
  auto r_last = std::make_reverse_iterator(first);
  auto left = std::is_sorted_until(r_first, r_last);
  if(left != r_last){
    auto right = std::upper_bound(r_first, left, *left);
    std::iter_swap(left, right);
  }
  std::reverse(left.base(), last);
  return left != r_last;
}