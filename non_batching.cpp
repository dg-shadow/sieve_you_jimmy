#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

bool run_sieve(int start, int run_size, vector<int> & primes, vector<bool> & sieve);
void prepare_sieve(int run, int start, int run_size, vector<int> & primes, vector<bool> & sieve);
void print(vector<bool> & sieve);
void print(vector<int> & primes);

int main(void)
{
  int start = 0;
  int run_size = 100000000;
  int n_runs = 1;
  int run = 0;
  vector<int> primes(1,2);
  vector<bool> sieve(run_size);

  // for (int run = 0; run < n_runs; ++run)
  // {
    prepare_sieve(run, start, run_size, primes, sieve);
    while (true)
    {
      bool tested_to_end_of_sieve = run_sieve(start + run * n_runs, run_size, primes, sieve);
      if (tested_to_end_of_sieve)
      {
        break;
      }
    }
  // }
  //print(primes);
    cout << primes.size() << endl;
  return 0;
}

void print(vector<bool> & sieve)
{
  for (int x = 0; x < sieve.size(); ++x)
  {
    cout << x << ": " << sieve[x] << ", ";
  }
  cout << endl; 
}

void print(vector<int> & primes)
{
 for (int x = 0; x < primes.size(); ++x)
  {
    cout << primes[x] << ", ";
  }
  cout << endl;
}

void prune_sieve(int start, int run_size, int prime, vector<bool> & sieve)
{
  int first_index = start + (prime % run_size);
  for (int x = first_index; x < run_size; x += prime)
  {
    sieve[x] = false;
  }
}

void prepare_sieve(int run, int start, int run_size, vector<int> & primes, vector<bool> & sieve)
{
  for (int x = 0; x < run_size; ++x)
  {
    sieve[x] = true;
  }
  if (run == 0)
  {
    sieve[0] = false;
    sieve[1] = false;
  }
  for (int prime_index = 0; prime_index < primes.size(); ++ prime_index)
  {
    prune_sieve(start, run_size, primes[prime_index], sieve);
  }
  // print(sieve);
}

bool run_sieve(int start, int run_size, vector<int> & primes, vector<bool> & sieve)
{
  int latest_prime = primes.back();

  // cout << "latest " << latest_prime << endl;

  prune_sieve(start, run_size, latest_prime, sieve);

  int prime_test_index;

  for (prime_test_index = latest_prime - start; prime_test_index < run_size; ++prime_test_index)
  {
    if (sieve[prime_test_index])
    {
      primes.push_back(start + prime_test_index);
      break;
    }
  }
  //print(primes);
  return (prime_test_index == run_size);
}
