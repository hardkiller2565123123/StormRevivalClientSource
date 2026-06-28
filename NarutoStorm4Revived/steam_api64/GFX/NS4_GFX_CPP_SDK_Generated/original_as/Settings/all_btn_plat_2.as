package script.xcmn_btn_plat
{
   import flash.display.MovieClip;
   
   public class all_btn_plat extends MovieClip
   {
      
      public static const CCD_BUTTON_R_RIGHT:String = "btn_1";
      
      public static const CCD_BUTTON_R_RIGHT_HOLD:String = "btn_1_hld";
      
      public static const CCD_BUTTON_R_DOWN:String = "btn_2";
      
      public static const CCD_BUTTON_R_DOWN_HOLD:String = "btn_2_hld";
      
      public static const CCD_BUTTON_R_LEFT:String = "btn_3";
      
      public static const CCD_BUTTON_R_LEFT_HOLD:String = "btn_3_hld";
      
      public static const CCD_BUTTON_R_UP:String = "btn_4";
      
      public static const CCD_BUTTON_R_UP_HOLD:String = "btn_4_hld";
      
      public static const CCD_BUTTON_R1:String = "btn_r1";
      
      public static const CCD_BUTTON_R1_HOLD:String = "btn_r1_hld";
      
      public static const CCD_BUTTON_L1:String = "btn_l1";
      
      public static const CCD_BUTTON_L1_HOLD:String = "btn_l1_hld";
      
      public static const CCD_BUTTON_R2:String = "btn_r2";
      
      public static const CCD_BUTTON_R2_HOLD:String = "btn_r2_hld";
      
      public static const CCD_BUTTON_L2:String = "btn_l2";
      
      public static const CCD_BUTTON_L2_HOLD:String = "btn_l2_hld";
      
      public static const CCD_BUTTON_KEY:String = "key";
      
      public static const CCD_BUTTON_KEY_UP:String = "key_up";
      
      public static const CCD_BUTTON_KEY_RIGHT:String = "key_r";
      
      public static const CCD_BUTTON_KEY_DOWN:String = "key_dwn";
      
      public static const CCD_BUTTON_KEY_LEFT:String = "key_l";
      
      public static const CCD_BUTTON_STK_R:String = "stk_r";
      
      public static const CCD_BUTTON_STK_R_ROLL:String = "stk_r_roll";
      
      public static const CCD_BUTTON_STK_R_RIGHT:String = "stk_r_r";
      
      public static const CCD_BUTTON_STK_R_LEFT:String = "stk_r_l";
      
      public static const CCD_BUTTON_STK_R_UP:String = "stk_r_up";
      
      public static const CCD_BUTTON_STK_R_DOWN:String = "stk_r_dwn";
      
      public static const CCD_BUTTON_STK_R3:String = "stk_r3";
      
      public static const CCD_BUTTON_STK_L:String = "stk_l";
      
      public static const CCD_BUTTON_STK_L_ROLL:String = "stk_l_roll";
      
      public static const CCD_BUTTON_STK_L_RIGHT:String = "stk_l_r";
      
      public static const CCD_BUTTON_STK_L_LEFT:String = "stk_l_l";
      
      public static const CCD_BUTTON_STK_L_UP:String = "stk_l_up";
      
      public static const CCD_BUTTON_STK_L_DOWN:String = "stk_l_dwn";
      
      public static const CCD_BUTTON_START:String = "btn_option";
      
      public static const CCD_BUTTON_SELECT:String = "pad";
      
      public static const CCD_BUTTON_KEY_PLUS:String = "icon_plus";
      
      public static const CCD_BUTTON_KEY_SHARE:String = "icon_share";
      
      public function all_btn_plat()
      {
         super();
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         visible = param1;
      }
      
      public function SetButtonId(param1:String) : *
      {
         gotoAndStop(param1);
      }
      
      public function SetPos(param1:Number, param2:Number) : *
      {
         x = param1;
         y = param2;
      }
      
      public function SetScale(param1:Number, param2:Number) : *
      {
         scaleX = param1;
         scaleY = param2;
      }
      
      public function IsVisible() : Boolean
      {
         return visible;
      }
   }
}

