#include "dialog.hpp"

void dialog::dialog(easy_dial& easy, const string& input, vector<string>& answers, nat& numtelf) throw() {
    nat i = 0;
    answers.push_back(easy.inici());
    for (i = 0; i < input.length(); ++i) {
      if (input[i] == '<') {
        answers.push_back(easy.anterior());
      }
      else if(input[i] == '|') {
        answers.push_back(easy.seguent('\0'));
      }
      else {
        answers.push_back(easy.seguent(input[i]));
      }
    }
    numtelf = easy.num_telf();
}