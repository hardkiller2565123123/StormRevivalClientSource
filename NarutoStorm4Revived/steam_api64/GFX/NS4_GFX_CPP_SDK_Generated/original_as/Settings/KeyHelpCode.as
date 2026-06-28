package KeyHelp
{
   import flash.external.ExternalInterface;
   
   public class KeyHelpCode
   {
      
      public static const CCD_BTN_ICON_R_RIGHT:String = "<icon btn_1 />";
      
      public static const CCD_BTN_ICON_R_DOWN:String = "<icon btn_2 />";
      
      public static const CCD_BTN_ICON_R_UP:String = "<icon btn_4 />";
      
      public static const CCD_BTN_ICON_R_LEFT:String = "<icon btn_3 />";
      
      public static const CCD_BTN_ICON_R1:String = "<icon btn_r1 />";
      
      public static const CCD_BTN_ICON_L1:String = "<icon btn_l1 />";
      
      public static const CCD_BTN_ICON_R2:String = "<icon btn_r2 />";
      
      public static const CCD_BTN_ICON_L2:String = "<icon btn_l2 />";
      
      public static const CCD_BTN_ICON_R_STICK:String = "<icon stk_r />";
      
      public static const CCD_BTN_ICON_L_STICK:String = "<icon stk_l />";
      
      public static const CCD_BTN_ICON_R3:String = "<icon stk_r3 />";
      
      public static const CCD_BTN_ICON_L3:String = "<icon stk_l3 />";
      
      public static const CCD_BTN_ICON_L_LEFT:String = "<icon key_l />";
      
      public static const CCD_BTN_ICON_L_UP:String = "<icon key_up />";
      
      public static const CCD_BTN_ICON_L_RIGHT:String = "<icon key_r />";
      
      public static const CCD_BTN_ICON_L_DOWN:String = "<icon key_dwn />";
      
      public static const CCD_BTN_ICON_L_LR:String = "<icon key_l /> <icon key_r />";
      
      public static const CCD_BTN_ICON_L_UD:String = "<icon key_up /> <icon key_dwn />";
      
      public static const CCD_BTN_ICON_LS_UP:String = "<icon stk_l_dwn />";
      
      public static const CCD_BTN_ICON_LS_DOWN:String = "<icon stk_l_dwn />";
      
      public static const CCD_BTN_ICON_START:String = "<icon start />";
      
      public static const CCD_BTN_ICON_SELECT:String = "<icon select />";
      
      public static const CCD_BTN_ICON_OK:String = "<icon ok />";
      
      public static const CCD_BTN_ICON_CANCEL:String = "<icon cancel />";
      
      public static const CCD_KEY_HELP_DECIDE:int = 0;
      
      public static const CCD_KEY_HELP_CANCEL:int = 1;
      
      public static const CCD_KEY_HELP_CONTINUE:int = 2;
      
      public static const CCD_KEY_HELP_NEXT:int = 3;
      
      public static const CCD_KEY_HELP_SKIP:int = 4;
      
      public static const CCD_KEY_HELP_SKIP2:int = 5;
      
      public static const CCD_KEY_HELP_OK:int = 6;
      
      public static const CCD_KEY_HELP_RETURN:int = 7;
      
      public static const CCD_KEY_HELP_CLOSE:int = 8;
      
      public static const CCD_KEY_HELP_CLOSE2:int = 9;
      
      public function KeyHelpCode()
      {
         super();
      }
      
      public function SetKeyHelpVisible(param1:Boolean) : *
      {
         ExternalInterface.call("SetKeyHelpVisible",param1);
      }
      
      public function AddKeyHelpStr(param1:String, param2:String) : *
      {
         ExternalInterface.call("AddKeyHelpStr",param1,param2);
      }
      
      public function AddKeyHelpId(param1:String, param2:String) : *
      {
         ExternalInterface.call("AddKeyHelpId",param1,param2);
      }
      
      public function AddKeyHelpTblId(param1:int) : *
      {
         ExternalInterface.call("AddKeyHelpTblId",param1);
      }
      
      public function DeleteKeyHelp() : *
      {
         ExternalInterface.call("DeleteKeyHelp");
      }
      
      public function PushKeyHelp(param1:Boolean = false) : *
      {
         ExternalInterface.call("PushKeyHelp",param1);
      }
      
      public function PopKeyHelp() : *
      {
         ExternalInterface.call("PopKeyHelp");
      }
   }
}

