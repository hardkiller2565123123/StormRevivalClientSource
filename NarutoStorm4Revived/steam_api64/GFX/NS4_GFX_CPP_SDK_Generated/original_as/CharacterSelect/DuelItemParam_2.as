package script.duel_item
{
   import Enum.Enum;
   
   public class DuelItemParam
   {
      
      public static const CCD_TYPE_NONE:int = Enum.Next(0);
      
      public static const CCD_TYPE_DOKI:int = Enum.Next();
      
      public static const CCD_ITEM_SKILL_ICON_TBL:Array = [[null,null,null,null],[null,"c_char_tyy1_b","c_char_tyy1_l","c_char_tyy1_r"]];
      
      public function DuelItemParam()
      {
         super();
      }
   }
}

