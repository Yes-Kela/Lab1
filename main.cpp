#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Prepare(double* resistance, int capacity);
int SelectData(double* resistance, int size);
double ComputeResult(double* resistance, int size);
int Check(double* resistance, double result, int size);
int iscorrect(double value, double reference);
int isequal(double a, double b);

const int MILLI = 1000;

int main(void)
{
    const int MAX_LEN = 100;

    double resistance[MAX_LEN] = {};
    printf("Enter voltage and amperage for all measurements (one measurement in one line)\n");
    printf("(Enter non-numeric value at the end):\n");
    int real_size = Prepare(resistance, MAX_LEN);

    int new_size = SelectData(resistance, real_size);

    double resistance_final = ComputeResult(resistance, new_size);

    if (Check(resistance, resistance_final, new_size) == 1)
    {
        printf("Congratulations!!! The mean deviation in absolute value is close to zero "
               "so result is correct!\n");
    }
    else
    {
        printf("Ooops! The mean deviation is quite big...\n"
               "Experiment didn't go according to plan...\n");
    }

    return 0;
}

int Prepare(double* resistance, int capacity)
{
    double* voltage  = (double*) calloc(capacity, sizeof(double));
    double* amperage = (double*) calloc(capacity, sizeof(double));

    int correct = 0;
    for (; correct < capacity; correct++)
    {
        double volt = 0, ampere = 0;
        if (scanf("%lf %lf", &volt, &ampere) == 2)
        {
            if (!isequal(ampere, 0) && !isequal(volt, 0))
            {
                voltage[correct] = volt;
                amperage[correct] = ampere;
            }
            else
            {
                free(voltage);
                free(amperage);
                return -1;
            }
        }
        else
        {
            break;
        }
    }

    for (int j = 0; j < correct; j++)
    {
        resistance[j] = voltage[j] / amperage[j] * MILLI;
    }

    free(voltage);
    free(amperage);
    return correct;
}


int SelectData(double* resistance, int size)
{
    double total = 0;
    for (int i = 0; i < size; i++)
    {
        total += resistance[i];
    }

    double resistance_average = total / size;

    int num_incorrect = 0;
    for (int i = 0; i < size; i++)
    {
        int flag = 0;
        if (!iscorrect(resistance[i], resistance_average))
        {
            int j = i;
            for (; j < size; j++)
            {
                if (iscorrect(resistance[j], resistance_average))
                {
                    num_incorrect = 0;
                    flag = 1;
                    break;
                }
                else
                {
                    num_incorrect++;
                }
            }
            double temp = resistance[i];
            resistance[i] = resistance[j];
            resistance[j] = temp;
        }
        if (flag == 0)
        {
            break;
        }
    }

    return (size - num_incorrect);
}

double ComputeResult(double* resistance, int size)
{
    double sum_resistance = 0, resistance_final = 0, deviation = 0, sum_delta_res = 0;

    for (int i = 0; i < size; i++)
    {
        sum_resistance += resistance[i];
    }

    resistance_final = sum_resistance/size;

    for (int j = 0; j < size; j++)
    {
        sum_delta_res += (resistance[j]- resistance_final)*(resistance[j]- resistance_final);
    }

    deviation = sqrt(sum_delta_res)/size;

    printf("The result is: (%g +- %g) Ohms\n", resistance_final, deviation);

    return resistance_final;
}

int Check(double* resistance, double result, int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += (resistance[i] - result);
    }
    return isequal(sum / size, 0);
}

int iscorrect(double value, double reference)
{
    if (fabs(value - reference) > 0.03 * reference)
    {
        return 0;
    }
    return 1;
}

int isequal(double a, double b)
{
    const double epsilon = 1e-5;
    if (fabs(a - b) < epsilon)
    {
        return 1;
    }
    return 0;
}
