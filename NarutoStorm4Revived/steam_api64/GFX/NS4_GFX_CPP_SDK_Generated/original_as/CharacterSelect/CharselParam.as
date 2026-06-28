package script.charsel
{
   import Enum.Enum;
   
   public class CharselParam
   {
      
      public static const CCD_STATE_LOOP:int = 0;
      
      public static const CCD_STATE_DECIDE:int = 1;
      
      public static const CCD_STATE_CANCEL:int = 2;
      
      public static const CCD_STATE_RETURN_LOOP:int = 3;
      
      public static const CCD_CHARSEL_PAGE_MAX_NUM:int = 5;
      
      public static const CCD_CHARSEL_FIRST_ROW_PANEL_1P:int = 25;
      
      public static const CCD_CHARSEL_FIRST_ROW_PANEL_2P:int = 27;
      
      public static const CCD_CHARSEL_NUM_TBL_WIDTH:Number = 3;
      
      public static const CCD_CHARSEL_NUM_TBL_HEIGHT:Number = 9;
      
      public static const CCD_CHARSEL_NUM_TBL:Array = [[1,2,3],[4,5,6],[7,8,9],[10,11,12],[13,14,15],[16,17,18],[19,20,21],[22,23,24],[25,26,27]];
      
      public static const CCD_CHARSEL_PRESET_MAX_NUM:int = 8;
      
      public static const CCD_SUPPORT_ACTION_REBOUND:int = Enum.Next(0);
      
      public static const CCD_SUPPORT_ACTION_DUSHCUT:int = Enum.Next();
      
      public static const CCD_SUPPORT_ACTION_SACRIFICE:int = Enum.Next();
      
      public static const CCD_SUPPORT_ACTION_GUARD:int = Enum.Next();
      
      public static const CCD_SUPPORT_ACTION_COVER:int = Enum.Next();
      
      public static const CCD_SUPPORT_ACTION_BREAK_GUARD:int = Enum.Next();
      
      public static const CCD_SUPPORT_ACTION_CHARGE_ASSIST:int = Enum.Next();
      
      public static const CCD_SUPPORT_ACTION_NUM:int = Enum.Next();
      
      public static const CCD_SUPPORT_ACTION_ICON_TBL:Array = ["../icon_assist/asst_at_counter.xfbin","../icon_assist/asst_sp_cut.xfbin","../icon_assist/asst_scf_oug.xfbin","../icon_assist/asst_sp_guard.xfbin","../icon_assist/asst_sp_cover.xfbin","../icon_assist/asst_at_guard.xfbin","../icon_assist/asst_sp_ckr.xfbin"];
      
      public function CharselParam()
      {
         super();
      }
   }
}

