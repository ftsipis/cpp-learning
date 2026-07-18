import std;

using namespace std;

double square(double x)
{
    return x*x;
}

void print_square(double x)
{
    cout<<"the square of"<<x<<"is"<<square(x)<<"\n";
}

int main()
{
    print square(1.234);
}