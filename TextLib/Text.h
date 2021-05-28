#pragma once
#include "TextNode.h"
#include <fstream>
#include <string>
class TextIter;

class Text {
protected:
  TextNode* root;
public:
  Text(char* s = 0);
  ~Text();

  TextIter GetRoot(); //Создание рут
  TextIter Find(char c); //Поиск буквы. Вернет итератор после найденой буквы
  TextIter Find(char* c); //Поиск. Вернет итератор после найденой буквы
  TextIter FindWord(char* c); //Поиск слова. Вернет итератор после найденого слова

  void Insert(char* c, TextIter i); //Вставить после i
  void InsertData(char* c, TextIter i);
  void InsertLine(char* c, TextIter i);
  void Delete(int count, TextIter i); //Удалить начиная с i, указанное количество букв
  char* Copy(int count, TextIter i); //Копирует указанное количество букв, начиная с i

  friend std::ostream& operator<<(std::ostream& o, Text& t);
};

class TextIter {
protected:
  Text& text;
  TextNode* node;
  TStack<TextNode*> st;
public:
  TextIter(Text& _text, TextNode* _node, TStack<TextNode*> _st);
  TextIter(const TextIter& t);

  bool GoNext(); //Перейти дальше
  bool GoNextChar(); //Перейти к следующей букве
  bool IsEnd(); //Првоерка конца

  void ResetToString();
  void ResetToWord();

  TextNode* Get(); //Получить весь текст
};


TextIter::TextIter(Text& _text, TextNode* _node, TStack<TextNode*> _st) : text(_text) {
  node = _node;
  st = _st;
}

TextIter::TextIter(const TextIter& t) : text(t.text)
{
  node = t.node;
  st = t.st;
}

bool TextIter::GoNext() //Переход дальше
{
  if (node->GetLevel() == 3)
  {
    if (node->GetNext() != 0)
    {
      node = node->GetNext();
    }
    else
    {
      node = st.Get();

      if (node->GetNext() != 0)
      {
        node = node->GetNext();
      }
      else
      {
        node = st.Get();
        if (node->GetNext() != 0)
        {
          node = node->GetNext();
        }
        else
        {
          node = 0;
          return false;
        }
      }
    }
  }
  else
  {
    st.Push(node);
    node = node->GetDown();
  }
  return true;
}

bool TextIter::GoNextChar()
{
  if (node->GetLevel() == 1)
  {
    st.Push(node);
    node = node->GetDown();
    st.Push(node);
    node = node->GetDown();
    return true;
  }

  if (node->GetLevel() == 2)
  {
    st.Push(node);
    node = node->GetDown();
    return true;
  }

  if (node->GetLevel() == 3 && node->GetNext() != nullptr)
  {
    node = node->GetNext();
    return true;
  }

  if (node->GetLevel() == 3 && node->GetNext() == nullptr)
  {
    if (st.IsEmpty())
    {
      throw - 1; //Переполнение стека
    }

    TextNode* temp = st.Get();

    if (temp->GetNext() != nullptr)
    {
      st.Push(temp->GetNext());
      node = temp->GetNext()->GetDown();
      return true;
    }

    return false;
  }
  return false;
}

bool TextIter::IsEnd()
{
  if (node == nullptr)
  {
    return true;
  }

  if (node->GetLevel() == 1 || node->GetLevel() == 2)
  {
    return false;
  }

  if (node->GetLevel() == 3 && node->GetNext() != nullptr)
  {
    return false;
  }

  if (node->GetLevel() == 3 && node->GetNext() == nullptr)
  {
    if (st.IsEmpty())
    {
      throw - 1; //Переполнение стека
    }

    TextNode* prev = st.Get();
    if (prev->GetNext() != nullptr)
    {
      return false;
    }

    return true;
  }

  return true;
}

void TextIter::ResetToString() {
  while (node->GetLevel() > 1)
  {
    if (st.IsEmpty())
    {
      throw - 1;
    }

    node = st.Get();
  }
}

void TextIter::ResetToWord()
{
  if (node->GetLevel() == 1)
  {
    st.Push(node);
    node = node->GetDown();
  }
  else if (node->GetLevel() == 3)
  {
    node = st.Get();
  }
}

TextNode* TextIter::Get()
{
  return node;
}

Text::Text(char* s)
{
  root = new TextNode(s, 1);
}

Text::~Text()
{
  TextNode::FreeMem();
}

TextIter Text::GetRoot()
{
  TStack<TextNode*> A(100);
  TextIter B(*this, root, A);
  return B;
}

TextIter Text::Find(char c)
{
  TextIter iter = GetRoot();

  while (iter.GoNextChar())
  {
    if (iter.Get()->GetC() == c)
    {
      return iter;
    }
  }
  return iter;
}

TextIter Text::FindWord(char* c)
{
  TStack<TextNode*> A(100);
  TextIter iter(*this, root, A);

  while (iter.GoNext())
  {
    if (iter.Get()->GetLevel() == 2)
    {
      TextIter resuls = iter;
      bool control = true;
      int i = 0;
      int n = strlen(c);

      while (iter.GoNext() && i < n)
      {
        if (iter.Get()->GetLevel() == 2)
        {
          control = false;
          break;
        }

        if (iter.Get()->GetC() != c[i])
        {
          control = false;
          break;
        }
        i++;
      }

      if (control)
      {
        return resuls;
      }
    }
  }
  return iter;
}

TextIter Text::Find(char* s)
{
  TStack<TextNode*> A(100);
  TextIter iter(*this, root, A);
  int n = strlen(s);

  while (iter.GoNextChar())
  {
    TextIter cur = iter;
    int i = 0;
    bool control = true;
    bool next = true;
    while (i < n)
    {
      if (!next)
      {
        control = false;
        break;
      }
      if (s[i] != cur.Get()->GetC()) {
        control = false;
        break;
      }
      next = cur.GoNextChar();
      i++;
    }

    if (control)
    {
      return iter;
    }
  }
}


void Text::Insert(char* c, TextIter i)
{
  TextNode* node = new TextNode(c, i.Get()->GetLevel());
  TextNode* next = i.Get()->GetNext();
  node->SetNext(next);
  i.Get()->SetNext(node);
}

inline void Text::InsertData(char* c, TextIter i)
{
  //Символ может быть побелом


  if (strlen(c) == 1) //Ситуация, когда получен символ
  {
    Insert(c, i);
  }
  else //Если чар* содержит больше 1 символа
  {
    int level = 2;
    int space = 0;

    for (int q = 0; q < strlen(c); q++)
    {
      if (c[q] == ' ') //Если есть пробел -> строка
      {
        level = 1;
        break;
      }
    }

    TextIter osn = i;
    TextNode* next = i.Get()->GetNext();

    if (next->GetC() == ' ' || next->GetC() == '.') //Если данные вставляются после слова (Next содержит пробел, точку)
    {
      i.GoNextChar(); //Переходим за пробел или точку
      int size = strlen(c);
      char* t = new char[strlen(c) + 1]; //Создаем новый чар, добавляем в конец пробел
      t[strlen(c) + 1] = '\0';

      for (int j = 0; j < strlen(c); j++)
      {
        t[j] = c[j];
      }
      t[strlen(c)] = ' ';

      TextNode* node = new TextNode(t, level);

      next->SetNext(node);
      i.Get()->SetNext(node);
    }
    else //Если данные вставляются в тело слова
    {
      int cc = 0;
      char symbol = ' ';
      TextNode* cc_node = i.Get()->GetNext();

      //Считаем длину остатка слова
      while ((cc_node->GetC() != '.') && (cc_node->GetC() != ' ') && (cc_node->GetC() != '\n'))
      {
        cc++;
        cc_node = cc_node->GetNext();
      }

      if (cc_node->GetC() == '.')
      {
        symbol = '.';
      }

      if (cc_node->GetC() == '\n')
      {
        symbol = '\n';
      }

      //Создаем итоговые данные для вставки(слово + пробел + остаток уже имеющегося слова + символ после него(пробел, точка, новая строка))
      char* temp = new char[strlen(c) + cc + 3];
      temp[strlen(c) + cc + 3] = '\0';
      temp[0] = ' ';

      int j = 1;
      int k = 0;
      for (j; j < strlen(c) + 1; j++, k++)
      {
        temp[j] = c[k];
      }
      temp[j] = ' ';

      TextNode* temp_node = i.Get()->GetNext();
      for (j = j + 1; j < strlen(c) + cc + 2; j++)
      {
        temp[j] = temp_node->GetC();
        temp_node = temp_node->GetNext();
      }

      temp[strlen(c) + cc + 2] = symbol;

      osn.GoNext();
      this->Delete(cc, osn);

      TextNode* node = new TextNode(temp, level);
      next->SetNext(node);
      i.Get()->SetNext(node);
    }
  }
}
void Text::InsertLine(char* c, TextIter iter)
{
	while (iter.Get()->GetC() != '\n')
		iter.GoNext();

	TextNode* node = new TextNode(c, 1);
	iter.Get()->SetNext(node);

	iter.GoNext();
	node = new TextNode("\n", 2);
	iter.Get()->SetNext(node);
}

void Text::Delete(int count, TextIter i)
{
  if (count == 0)
  {
    return;
  }

  TStack<TextNode*> stack[3];
  int del = 0;
  int level = i.Get()->GetLevel();
  //Перейти к букве, с которой нужно удалять
  if (level < 3)
  {
    i.GoNextChar();
  }

  if (level >= 1 && level <= 3)
  {
    stack[level - 1].Push(i.Get());
    if (level == 3)
    {
      del++;
    }
  }

  TextIter iter = i;
  while (iter.GoNext() && del < count)
  {
    level = iter.Get()->GetLevel();

    if (level >= 1 && level <= 3)
    {
      stack[level - 1].Push(iter.Get());

      if (level == 3)
      {
        del++;
      }
    }
  }

  if (del < count)
    throw - 1;

  //Удаление букв в одном слове
  if (stack[0].IsEmpty() && stack[1].IsEmpty())
  {
    TextIter prev = i;
    prev.ResetToWord();
    while (prev.Get()->GetNext() != i.Get() && prev.Get()->GetDown() != i.Get())
    {
      prev.GoNext();
    }
    TextNode* last = stack[2].Get();
    if (prev.Get()->GetLevel() == 2)
    {
      prev.Get()->SetDown(last->GetNext());
    }
    else
    {
      prev.Get()->SetNext(last->GetNext());
    }
    delete last;
    return;
  }

  //Установка nulltr для буквы, после которой начинается удаление
  TextIter prev = i;
  prev.ResetToWord();

  while (prev.Get()->GetNext() != i.Get() && prev.Get()->GetDown() != i.Get())
  {
    prev.GoNext();
  }

  if (prev.Get()->GetNext() == i.Get())
  {
    prev.Get()->SetNext(nullptr);
  }

  else
  {
    prev.Get()->SetDown(nullptr);
  }

  if (stack[0].IsEmpty()) //Удаление букв в одной строке
  {
    TextNode* last_word = stack[1].Get();
    TextNode* last_letter = stack[2].Get();
    TextIter cur = i;
    cur.ResetToWord();
    cur.Get()->SetNext(last_word);
    last_word->SetDown(last_letter->GetNext());
    delete last_letter;
    for (int i = 1; i < 3; i++)
    {
      while (!stack[i].IsEmpty())
      {
        TextNode* del = stack[i].Get();
        delete del;
      }
    }
  }
  else //Удаление букв в разных строках
  {
    TextNode* last_string = stack[0].Get();
    TextNode* last_word = stack[1].Get();
    TextNode* last_letter = stack[2].Get();
    TextIter cur = i;
    cur.ResetToString();
    cur.Get()->SetNext(last_string);
    cur.ResetToWord();
    cur.Get()->SetNext(last_word);
    last_word->SetDown(last_letter->GetNext());
    delete last_letter;

    for (int i = 0; i < 3; i++)
    {
      while (!stack[i].IsEmpty())
      {
        TextNode* temp = stack[i].Get();
        delete temp;
      }
    }
  }
}

char* Text::Copy(int count, TextIter i)
{
  if (count < 0)
  {
    throw - 1;
  }

  char* res = new char[count + 1];
  TextIter iter = i;

  while (iter.Get()->GetLevel() < 3)
  {
    iter.GoNext();
  }

  if (count > 0)
  {
    res[0] = iter.Get()->GetC();
    int j = 1;

    while (iter.GoNextChar() && j < count)
    {
      res[j] = iter.Get()->GetC();
      j++;
    }
  }

  res[count] = '\0';
  return res;
}

std::ostream& operator<<(std::ostream& out, Text& t)
{
  out << *(t.root);
  return out;
}