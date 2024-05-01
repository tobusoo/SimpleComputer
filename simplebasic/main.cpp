#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

struct Variable
{
  int address = 0;
  int value = 0;
};

struct AsmCommand
{
  std::string command;
  std::string operand;
};

enum Command
{
  REM,
  INPUT,
  OUTPUT,
  GOTO,
  IF,
  LET,
  END,
  UNKNOWN
};

std::unordered_map<char, Variable> sym_table;
std::unordered_map<int, char> const_to_sym;
std::unordered_map<int, int> basic_cmd_addr;
std::set<int> goto_addresses;
std::vector<AsmCommand> command_buffer;
std::vector<AsmCommand> out;

int current_line = 0;
int variable_address = 127;
int cmd_address = 0;
bool is_end = false;
bool use_command_buffer = false;

void
print_error (const std::string &msg)
{
  std::cerr << "Error at line ";
  std::cerr << current_line << ": " << msg << '\n';
  exit (EXIT_FAILURE);
}

void
is_line_number_correct (int line_number)
{
  static int prev_line_number = -1;
  if (line_number < prev_line_number)
    print_error ("Wrong line number");

  prev_line_number = line_number;
}

void
assembler (const std::string &command, const std::string &operand)
{
  if (!use_command_buffer)
    out.push_back ({ command, operand }), cmd_address++;
  else
    command_buffer.push_back ({ command, operand });
}

Command
parse_command (const std::string &command)
{
  if (command == "REM")
    return REM;
  if (command == "INPUT")
    return INPUT;
  if (command == "OUTPUT")
    return OUTPUT;
  if (command == "GOTO")
    return GOTO;
  if (command == "IF")
    return IF;
  if (command == "LET")
    return LET;
  if (command == "END")
    return END;

  return UNKNOWN;
}

std::vector<std::string>
get_lexems (const std::string &line)
{
  auto iss = std::istringstream (line);
  std::vector<std::string> lexems;
  std::string lexem;

  while (iss >> lexem)
    {
      lexems.push_back (lexem);
    }

  return lexems;
}

bool
is_constant (char ch)
{
  return ch >= 'a';
}

void
sym_table_add (const char variable)
{
  if (variable < 'A' || variable > 'Z')
    print_error ("Invalid variable");
  if (sym_table.count (variable) == 0)
    {
      sym_table[variable].address = variable_address;
      variable_address--;
    }
}

void
sym_table_add_constant (int constant)
{
  static char sym = 'a';

  if (const_to_sym.count (constant) == 0)
    {
      const_to_sym[constant] = sym;
      sym_table[sym] = { variable_address--, constant };
      sym++;
    }
}

std::string
int_to_str (int value)
{
  std::stringstream stream;
  stream << std::hex << std::uppercase << std::setfill ('0') << std::setw (4);
  stream << std::abs (value);

  if (value < 0)
    return '-' + stream.str ();
  return '+' + stream.str ();
}

void
input_translate (std::vector<std::string> &lexems)
{
  if (lexems.size () > 3)
    print_error ("To many lexems");

  auto variable_str = lexems.size () >= 3 ? lexems[2] : "";
  if (variable_str.size () > 1)
    print_error ("Invalid variable");

  auto variable = variable_str[0];
  sym_table_add (variable);

  assembler ("READ", std::to_string (sym_table[variable].address));
}

void
output_translate (std::vector<std::string> &lexems)
{
  if (lexems.size () > 3)
    print_error ("To many lexems");

  auto variable_str = lexems.size () >= 3 ? lexems[2] : "";
  if (variable_str.size () > 1)
    print_error ("Invalid variable");

  auto variable = variable_str[0];
  sym_table_add (variable);

  assembler ("WRITE", std::to_string (sym_table[variable].address));
}

char
rpn_constant (std::string &expr)
{
  if (expr[0] != '-')
    return '\0';

  for (size_t i = 1; i < expr.size (); i++)
    {
      if (!isdigit (expr[i]))
        print_error ("Invalid constant");
    }

  int constant = std::atoi (expr.c_str ());
  sym_table_add_constant (constant);
  return const_to_sym[constant];
}

void
is_correct_expr (std::string &expr, std::map<char, int> &op_prior)
{
  for (size_t i = 1; i < expr.size (); i++)
    {
      bool is_op = op_prior.count (expr[i]);
      bool is_prev_op = op_prior.count (expr[i - 1]);
      if (is_op && is_prev_op)
        print_error ("Invalid expression");
    }
}

std::string
rpn (std::string &expr)
{
  std::string rpn;
  std::stack<char> s;
  std::map<char, int> op_prior = {
    { '(', 0 }, { '+', 1 }, { '-', 1 }, { '*', 2 }, { '/', 2 },
  };

  if (expr.size () == 1 && op_prior.count (expr[0]) == 1)
    print_error ("Invalid expression");

  auto res = rpn_constant (expr);
  if (res != '\0')
    return rpn + res;
  is_correct_expr (expr, op_prior);

  for (size_t i = 0; i < expr.size (); i++)
    {
      size_t j = i;
      while (isdigit (expr[i]))
        i++;
      if (j != i)
        {
          int constant = std::atoi (expr.c_str () + j);
          sym_table_add_constant (constant);
          rpn += const_to_sym[constant];
          continue;
        }

      char ch = expr[i];
      if (ch >= 'A' && ch <= 'Z')
        {
          rpn += ch;
          sym_table_add (ch);
        }
      else if (ch == '(')
        s.push (ch);
      else if (ch == ')')
        {
          while (!s.empty () && s.top () != '(')
            {
              rpn += s.top ();
              s.pop ();
            }
          if (s.empty ())
            print_error ("Invalid expression");
          s.pop ();
        }
      else if (op_prior.count (ch) == 1)
        {
          while (!s.empty () && op_prior[s.top ()] >= op_prior[ch])
            {
              rpn += s.top ();
              s.pop ();
            }
          s.push (ch);
        }
      else
        print_error ("Invalid character in the expression");
    }

  while (!s.empty ())
    {
      char ch = s.top ();
      rpn += ch;
      s.pop ();
    }

  return rpn;
}

void
rpn_asm (std::stack<char> s, char ch, bool &is_accum_clear)
{
  if (s.empty ())
    print_error ("Invalid expression");
  char operand1 = s.top (), operand2;
  s.pop ();

  if (is_accum_clear)
    {
      if (s.empty ())
        print_error ("Invalid expression");
      operand2 = s.top ();
      s.pop ();
      is_accum_clear = false;
      assembler ("LOAD", std::to_string (sym_table[operand2].address));
    }

  switch (ch)
    {
    case '+':
      assembler ("ADD", std::to_string (sym_table[operand1].address));
      break;
    case '-':
      assembler ("SUB", std::to_string (sym_table[operand1].address));
      break;
    case '*':
      assembler ("MUL", std::to_string (sym_table[operand1].address));
      break;
    case '/':
      assembler ("DIVIDE", std::to_string (sym_table[operand1].address));
      break;
    default:
      print_error ("Invalid operator " + ch);
    }
}

int
rpn_translate (std::string &rpn)
{
  std::stack<char> s;
  int command_count = 0;
  bool is_accum_clear = true;

  if (rpn.size () == 1)
    {
      assembler ("LOAD", std::to_string (sym_table[rpn[0]].address));
      return 1;
    }

  for (size_t i = 0; i < rpn.size (); i++)
    {
      char ch = rpn[i];
      if ((ch >= 'A' && ch <= 'Z') || is_constant (ch))
        s.push (ch);
      else
        {
          rpn_asm (s, ch, is_accum_clear);
          command_count++;
        }
    }

  return command_count;
}

int
let_translate (std::vector<std::string> &lexems)
{
  int command_count = 0;
  auto variable_str = lexems.size () >= 3 ? lexems[2] : "";
  if (variable_str.size () > 1)
    print_error ("Invalid variable");

  auto variable = variable_str[0];
  sym_table_add (variable);

  std::string expr;
  auto equal_str = lexems.size () >= 4 ? lexems[3] : "";
  if (equal_str == "=")
    for (size_t i = 4; i < lexems.size (); i++)
      expr += lexems[i];
  else
    print_error ("Expected \"=\"");

  if (expr.size () == 0)
    print_error ("Empty expression");

  auto rpn_str = rpn (expr);
  command_count += rpn_translate (rpn_str);

  assembler ("STORE", std::to_string (sym_table[variable].address));

  return command_count + 1;
}

void
goto_translate (std::vector<std::string> &lexems)
{
  auto address_str = lexems.size () >= 3 ? lexems[2] : "";
  int address_basic;
  try
    {
      address_basic = std::stoi (address_str);
    }
  catch (std::exception &e)
    {
      print_error ("Invalid goto address: " + address_str);
    }
  goto_addresses.insert (address_basic);
  assembler ("JUMP", std::to_string (address_basic));
}

std::tuple<char, char, char>
if_parse_operands (std::string &expr)
{
  size_t i, j;
  char operand1, operand2, op;
  i = 0, j = 0;
  while (isdigit (expr[i]))
    i++;
  if (i != j)
    {
      int constant = std::atoi (expr.c_str () + j);
      sym_table_add_constant (constant);
      operand1 = const_to_sym[constant];
      op = expr[i];
    }
  else
    {
      operand1 = expr[0];
      sym_table_add (operand1);
      op = expr[i + 1];
      i++;
    }

  j = ++i;
  while (isdigit (expr[i]))
    i++;
  if (i != j)
    {
      int constant = std::atoi (expr.c_str () + j);
      sym_table_add_constant (constant);
      operand2 = const_to_sym[constant];
    }
  else
    {
      operand2 = expr[i];
      sym_table_add (operand2);
    }

  return { operand1, op, operand2 };
}

void
asm_compare (char operand1, char op, char operand2)
{
  switch (op)
    {
    case '>':
      assembler ("LOAD", std::to_string (sym_table[operand2].address));
      assembler ("SUB", std::to_string (sym_table[operand1].address));
      assembler ("JNEG", std::to_string (cmd_address + 2));
      break;
    case '<':
      assembler ("LOAD", std::to_string (sym_table[operand1].address));
      assembler ("SUB", std::to_string (sym_table[operand2].address));
      assembler ("JNEG", std::to_string (cmd_address + 2));
      break;
    case '=':
      assembler ("LOAD", std::to_string (sym_table[operand1].address));
      assembler ("SUB", std::to_string (sym_table[operand2].address));
      assembler ("JNEG", std::to_string (cmd_address + 3));
      assembler ("JNS", std::to_string (cmd_address + 2));
      break;
    default:
      print_error ("Invalid operator " + op);
      break;
    }
}

int
after_if_translate (Command &command, std::vector<std::string> &lexems)
{
  int command_count = 0;
  use_command_buffer = true;
  switch (command)
    {
    case REM:
      return 0;
    case INPUT:
      input_translate (lexems);
      command_count++;
      break;
    case OUTPUT:
      output_translate (lexems);
      command_count++;
      break;
    case GOTO:
      goto_translate (lexems);
      command_count++;
      break;
    case IF:
      print_error ("The use of 2 IF is prohibited");
    case LET:
      command_count += let_translate (lexems);
      break;
    case END:
      assembler ("HALT", "0");
      command_count++;
      is_end = true;
      break;
    default:
      print_error ("Invalid command");
    }
  use_command_buffer = false;

  return command_count;
}

void
if_translate (std::vector<std::string> &lexems)
{
  std::string expr;
  size_t k;

  for (k = 2; k < lexems.size (); k++)
    {
      auto command = parse_command (lexems[k]);
      if (command == UNKNOWN)
        expr += lexems[k];
      else
        break;
    }
  if (expr.size () < 3)
    print_error ("Wrong expression");

  auto [operand1, op, operand2] = if_parse_operands (expr);
  asm_compare (operand1, op, operand2);

  int else_address = cmd_address;
  auto command_str = k != lexems.size () ? lexems[k] : "";
  auto command = parse_command (command_str);
  lexems.erase (lexems.begin (), lexems.begin () + k - 1);
  int command_count = after_if_translate (command, lexems);
  else_address += command_count + 1;

  if (op != '=')
    assembler ("JUMP", std::to_string (else_address));

  for (auto &&i : command_buffer)
    assembler (i.command, i.operand);
  command_buffer.clear ();
}

void
command_translate (Command command, std::vector<std::string> &lexems)
{
  switch (command)
    {
    case REM:
      return;
    case INPUT:
      input_translate (lexems);
      break;
    case OUTPUT:
      output_translate (lexems);
      break;
    case GOTO:
      goto_translate (lexems);
      break;
    case IF:
      if_translate (lexems);
      break;
    case LET:
      let_translate (lexems);
      break;
    case END:
      assembler ("HALT", "0");
      is_end = true;
      break;
    default:
      print_error ("Invalid command");
    }
}

void
line_translation (const std::string &line)
{
  auto lexems = get_lexems (line);
  int line_number;
  try
    {
      line_number = std::stoi (lexems[0]);
    }
  catch (std::exception &e)
    {
      print_error ("Invalid line number: " + lexems[0]);
    }
  current_line = line_number;
  is_line_number_correct (line_number);

  auto command_str = lexems.size () >= 2 ? lexems[1] : "";
  auto command = parse_command (command_str);
  basic_cmd_addr[line_number] = cmd_address;
  command_translate (command, lexems);
}

int
goto_asm_addr (std::string &basic_addr)
{
  int addr;
  try
    {
      addr = std::stoi (basic_addr);
    }
  catch (std::exception &e)
    {
      print_error ("Invalid goto address: " + basic_addr);
    }
  bool addr_exist = basic_cmd_addr.find (addr) != basic_cmd_addr.end ();
  bool is_goto_addr = goto_addresses.find (addr) != goto_addresses.end ();

  if (addr_exist && is_goto_addr)
    return basic_cmd_addr[addr];
  else if (is_goto_addr)
    print_error ("Invalid goto address");

  return addr;
}

void
write_to_asm_file (std::ofstream &assembler_file)
{
  int cmd_address = 0;
  for (auto &&asm_command : out)
    {
      assembler_file << cmd_address << ' ';
      assembler_file << asm_command.command << ' ';
      if (asm_command.command == "JUMP")
        assembler_file << goto_asm_addr (asm_command.operand) << '\n';
      else
        assembler_file << asm_command.operand << '\n';
      cmd_address++;
    }

  for (auto &&[ch, variable] : sym_table)
    {
      assembler_file << variable.address << " = ";
      assembler_file << int_to_str (variable.value);
      assembler_file << " ; ";
      if (is_constant (ch))
        assembler_file << variable.value << '\n';
      else
        assembler_file << ch << '\n';
    }
}

int
main (int argc, char *argv[])
{
  if (argc != 3)
    {
      std::cerr << "Usage: ";
      std::cerr << argv[0] << " <in.sb> <out.sa>\n";
      exit (EXIT_FAILURE);
    }

  std::ifstream file (argv[1]);
  if (!file.is_open ())
    {
      std::cerr << "Couldn't open \"" << argv[2] << "\": ";
      perror (" ");
      exit (EXIT_FAILURE);
    }

  std::string line;
  while (std::getline (file, line) && !is_end)
    line_translation (line);

  std::ofstream assembler_file (argv[2]);
  if (!file.is_open ())
    {
      std::cerr << "Couldn't open \"" << argv[2] << "\": ";
      perror (" ");
      exit (EXIT_FAILURE);
    }
  write_to_asm_file (assembler_file);

  return 0;
}