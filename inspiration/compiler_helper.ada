with Ada.Text_IO; use Ada.Text_IO;

package body Compiler_Helper is
   
   type Token_Type is (T_INT, T_FLOAT, T_IDENT, T_PLUS, T_SEMICOLON, T_EOF);
   
   type Token is record
      Token_Kind : Token_Type;
      Value      : String(1..100);
      Line       : Integer;
   end record;
   
   type FCC_Config is record
      Verbose     : Boolean;
      Debug       : Boolean;
      Output_File : String(1..256);
   end record;
   
   procedure Lexer_Analysis(Filename : in String) is
      Current_Token : Token;
   begin
      Put_Line("ADA Analyzing: " & Filename);
      Put_Line("   FCC style but in pure Ada!");
   end Lexer_Analysis;
   
   procedure Generate_Code(Config : in FCC_Config) is
   begin
      if Config.Verbose then
         Put_Line("ADA Generating code for: " & Config.Output_File);
      end if;
      Put_Line("   Ada could compile C too!");
   end Generate_Code;
   
end Compiler_Helper;
