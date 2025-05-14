#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct veiculo {
  char placa[8];      // placa do veículo
  char modelo[50];    // modelo do veículo
  int tipo;           // 1 = Carro, 2 = Moto, 3 = Caminhão
  float consumo;      // Km/litro
};

// Controller: Preenche as informações do veículo
void cadastrarVeiculo(struct veiculo *d) {
  printf("Placa: ");
  scanf(" %[^\n]", d->placa);

  printf("Modelo: ");
  scanf(" %[^\n]", d->modelo);

  do {
    printf("Tipo de Veículo (Carro: 1, Moto:2, Caminhão:3): ");
    scanf("%d", &d->tipo);
    if (d->tipo < 1 || d->tipo > 3) {
      printf("Tipo inválido! Tente novamente.\n");
    }
  } while (d->tipo < 1 || d->tipo > 3);

  printf("Consumo (Km/l): ");
  scanf("%f", &d->consumo);
}

// View: Exibe um veículo
void exibirVeiculo(struct veiculo d) {
  printf("\nPlaca: %s", d.placa);
  printf("\nModelo: %s", d.modelo);
  printf("\nConsumo: %.2f Km/l", d.consumo);
  printf("\nTipo: ");
  if (d.tipo == 1) {
    printf("CARRO");
  } else if (d.tipo == 2) {
    printf("MOTO");
  } else if (d.tipo == 3) {
    printf("CAMINHÃO");
  } else {
    printf("TIPO DESCONHECIDO");
  }
  printf("\n");
}

// Salva veículos no arquivo
void salvarVeiculos(struct veiculo *lista, int quantidade, const char *lista_veic) {
  FILE *fp = fopen(lista_veic, "w");
  if (fp == NULL) {
    printf("Erro ao abrir %s para escrita\n", lista_veic);
    return;
  }
  for (int i = 0; i < quantidade; i++) {
    fprintf(fp, "%s;%s;%d;%.2f\n", lista[i].placa, lista[i].modelo, lista[i].tipo, lista[i].consumo);
  }
  fclose(fp);
  printf("Veículos salvos com sucesso no arquivo '%s'.\n", lista_veic);
}

// Função principal com menu
int main() {
  struct veiculo *frota = NULL;
  int quantidade = 0;
  int opcao;

  do {
    printf("\n=== MENU GESTÃO DE FROTAS ===\n");
    printf("1 - Listar veículos\n");
    printf("2 - Cadastrar novo veículo\n");
    printf("3 - Salvar e sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      if (quantidade == 0) {
        printf("Nenhum veículo cadastrado.\n");
      } else {
        printf("\n--- Veículos Cadastrados ---\n");
        for (int i = 0; i < quantidade; i++) {
          exibirVeiculo(frota[i]);
        }
      }
    } else if (opcao == 2) {
      frota = realloc(frota, (quantidade + 1) * sizeof(struct veiculo));
      if (frota == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
      }
      printf("\n--- Cadastro do Veículo %d ---\n", quantidade + 1);
      cadastrarVeiculo(&frota[quantidade]);
      quantidade++;
      printf("Veículo cadastrado com sucesso!\n");
    } else if (opcao == 3) {
      salvarVeiculos(frota, quantidade, "frota.txt");
      printf("Saindo do sistema...\n");
    } else {
      printf("Opção inválida! Tente novamente.\n");
    }

  } while (opcao != 3);

  free(frota);
  return 0;
}
