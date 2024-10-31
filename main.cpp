#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Prepare(double* array, int capacity);
int SelectData(double* array, int size);
double ComputeResult(double* array, int size);
int Check(double* array, double result, int size);
int iscorrect(double value, double reference);
int isequal(double a, double b);

int main(void)
{
    const int MAX_LEN = 100;

    double resistance[MAX_LEN] = {};
    int real_size = Prepare(resistance, MAX_LEN);

    int new_size = SelectData(resistance, real_size);
    printf("new_size = %d\n", new_size);
    /*
    double resistance_final = ComputeResult(resistance, new_size);

    Check(resistance, resistance_final, new_size);
    */
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
                //printf("Alright!\n");
                voltage[correct] = volt;
                amperage[correct] = ampere;
            }
            else
            {
                //printf("\n***\nVoltage or amperage cannot be null! Try again!\n***\n");
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
        resistance[j] = voltage[j] / amperage[j];
    }

    free(voltage);
    free(amperage);
    return correct;
}


int SelectData(double* array, int size)
{
    double total = 0;
    for (int i = 0; i < size; i++)
    {
        total += array[i];
    }

    double array_average = total / size;

    int num_incorrect = 0;
    for (int i = 0; i < size; i++)
    {
        int flag = 0;
        if (!iscorrect(array[i], array_average))
        {
            int j = i;
            for (; j < size; j++)
            {
                if (iscorrect(array[j], array_average))
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
            double temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        if (flag == 0)
        {
            break;
        }
    }

    return (size - num_incorrect);
}

/*
double ComputeResult(double* array, int size)
{
}

int Check(double* array, double result, int size)
{
}
*/

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


