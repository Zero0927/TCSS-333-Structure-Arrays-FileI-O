//Siyuan Zhou

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Item {
    char item_name[30];
    int quantity;
    float price;
    float total_value;
};

struct Customer {
    char customer_name[30];
    int item_quantity;
    struct Item items[10];
    float total_value;
};

int getdata(struct Customer *customer, int customer_number) {
    int i = 0, j = 0;

    while(i<customer_number){
        printf("\ncustomer:<%s><%.2f>\n", customer[i].customer_name, customer[i].total_value);
        for (j = 0; j < customer[i].item_quantity; j++) {
            printf("          items:<%s><%d><%.2f><%.2f>\n",
                    customer[i].items[j].item_name,
                    customer[i].items[j].quantity,
                    customer[i].items[j].price,
                    customer[i].items[j].total_value
                    );
        }
        i++;
    }
    return 0;
}

int initialize(struct Customer *customer) {
    int i = 0, j = 0;
    for (i = 0; i < 20; i++) {
        customer[i].item_quantity = 0;
        while (j<10){
            customer[i].items[j].quantity = 0;
            customer[i].items[j].price = 0.0;
            j++;
        }
    }
    
    return 0;
}

int readfile(struct Customer *customer, int *customerNum) {
    FILE * file;
    
    if ((file = fopen("hw4input.txt", "rt")) == NULL) {
        printf("Can't open hw4input.txt\n");
        return -1;
    }
    
    int i = 0;
    struct Customer *temp = (struct Customer*) malloc(sizeof (struct Customer));
    char point;
    int end = 0;
    
    while (1) {
        
        end = fscanf(file, "%s %d %s %c%f",
                (temp->customer_name),
                &(temp->items[temp->item_quantity].quantity),
                (temp->items[temp->item_quantity].item_name),
                &(point),
                &(temp->items[temp->item_quantity].price));

        if (end < 0)
            break;
        
        for (i = 0; i<*customerNum; i++) {
            if (strcmp(customer[i].customer_name, temp->customer_name) == 0) {
                customer[i].items[customer[i].item_quantity].quantity = temp->items[temp->item_quantity].quantity;
                strcpy(customer[i].items[customer[i].item_quantity].item_name, temp->items[temp->item_quantity].item_name);
                customer[i].items[customer[i].item_quantity].price = temp->items[temp->item_quantity].price;
                customer[i].item_quantity++;
                break;
            }
        }
        if (i == *customerNum) {
            strcpy(customer[i].customer_name, temp->customer_name);
            customer[i].items[customer[i].item_quantity].quantity = temp->items[temp->item_quantity].quantity;
            strcpy(customer[i].items[customer[i].item_quantity].item_name, temp->items[temp->item_quantity].item_name);
            customer[i].items[customer[i].item_quantity].price = temp->items[temp->item_quantity].price;
            customer[i].item_quantity++;
            (*customerNum)++;
        }
    }

    free(temp);
    return 0;
}

int Output_time(struct Customer *customer, int customer_number) {
    int i = 0, j = 0;
    FILE * file = fopen("hw4time.txt", "w");
 
    while(i< customer_number){
        fprintf(file, "\n%s\n", customer[i].customer_name);
        for (j = 0; j < customer[i].item_quantity; j++) {
            fprintf(file, "%s %d $%.2f\n",
                    customer[i].items[j].item_name,
                    customer[i].items[j].quantity,
                    customer[i].items[j].price
                    );
        }
        i++;
    }
    return 0;
}

int Output_money(struct Customer *customer, int customer_number) {
    int i = 0, j = 0;
    FILE * file = fopen("hw4money.txt", "w");
    
    while( i < customer_number){
        fprintf(file, "\n%s, Total Order = $%.2f\n",
                customer[i].customer_name, customer[i].total_value);
        for (j = 0; j < customer[i].item_quantity; j++) {
            fprintf(file, "%s %d $%.2f, Item Value = $%.2f\n",
                    customer[i].items[j].item_name,
                    customer[i].items[j].quantity,
                    customer[i].items[j].price,
                    customer[i].items[j].total_value
                    );
        }
        i++;
    }
    return 0;
}

int sort(struct Customer *customer, int customer_number) {
    int i = 0, j = 0;
    for (i = 0; i < customer_number; i++) {
        customer[i].total_value = 0;
        for (j = 0; j < customer[i].item_quantity; j++) {
            customer[i].items[j].total_value =
                    customer[i].items[j].quantity * customer[i].items[j].price;
            customer[i].total_value += customer[i].items[j].total_value;
        }
    }

    for (i = 0; i < customer_number; i++) {
        sortItems(&customer[i]);
    }
    
    sortCustomers(customer, customer_number);
    
    return 0;
}

int sortItems(struct Customer *customer) {
    int i = 0, j = 0;

    while(i < customer->item_quantity){
        for (j = customer->item_quantity - 1; j > i; j--) {
            if (customer->items[j].total_value > customer->items[i].total_value) 
                swap_item(&(customer->items[j]), &(customer->items[i]));
            
        }
        i++;
    }
    return 0;
}

int sortCustomers(struct Customer *customer, int customer_number) {
    int i = 0, j = 0;
   // for (i = 0; i < customer_number; i++) {
        while(i<customer_number){
        for (j = customer_number - 1; j > i; j--) {
            if (customer[j].total_value > customer[i].total_value) {
                swap_customer(&customer[i], &customer[j]);
            }
        }
        i++;
    }
    return 0;
}

int swap_item(struct Item *item1, struct Item *item2) {
    struct Item *item = (struct Item*) malloc(sizeof (struct Item));

    strcpy(item->item_name, item1->item_name);
    item->quantity = item1->quantity;
    item->price = item1->price;
    item->total_value = item1->total_value;

    strcpy(item1->item_name, item2->item_name);
    item1->quantity = item2->quantity;
    item1->price = item2->price;
    item1->total_value = item2->total_value;

    strcpy(item2->item_name, item->item_name);
    item2->quantity = item->quantity;
    item2->price = item->price;
    item2->total_value = item->total_value;
    
    free(item);
    return 0;
}

int swap_customer(struct Customer *customer1, struct Customer *customer2) {
    int i = 0;
    struct Customer *customer = (struct Customer*) malloc(sizeof (struct Customer));
    
    strcpy(customer->customer_name, customer1->customer_name);
    customer->item_quantity = customer1->item_quantity;
    customer->total_value = customer1->total_value;
    
    for (i = 0; i < customer->item_quantity; i++) {
        swap_item(&(customer->items[i]), &(customer1->items[i]));
    }

    strcpy(customer1->customer_name, customer2->customer_name);
    customer1->item_quantity = customer2->item_quantity;
    customer1->total_value = customer2->total_value;
    
    for (i = 0; i < customer1->item_quantity; i++) {
        swap_item(&(customer1->items[i]), &(customer2->items[i]));
    }

    strcpy(customer2->customer_name, customer->customer_name);
    customer2->item_quantity = customer->item_quantity;
    customer2->total_value = customer->total_value;
    
    for (i = 0; i < customer2->item_quantity; i++) {
        swap_item(&(customer2->items[i]), &(customer->items[i]));
    }

    free(customer);
    return 0;
}

int main() {
    
    struct Customer customer[20];
    int customerNum = 0;
    initialize(customer);

    if (readfile(customer, &customerNum) < 0)
        return 0;

    Output_time(customer, customerNum);
    sort(customer, customerNum);
    Output_money(customer, customerNum);

    return 0;
}