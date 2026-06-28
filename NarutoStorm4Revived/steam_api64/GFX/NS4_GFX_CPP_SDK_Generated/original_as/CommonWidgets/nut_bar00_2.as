package script.freebtl_prac
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base4;
   import script.xcmn_menu.nut_base5;
   import script.xcmn_menu.nut_cursor_m;
   import script.xcmn_menu.nut_sel2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class nut_bar00 extends MovieClip
   {
      
      public var mc_arrow_l:nut_cursor_m;
      
      public var mc_arrow_r:nut_cursor_m;
      
      public var mc_base1:nut_base4;
      
      public var mc_base2:nut_base5;
      
      public var mc_sel:nut_sel2;
      
      public var txt_nomal:smb_font;
      
      public var txt_select:smb_font;
      
      public var txt_title:smb_font;
      
      public function nut_bar00()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4,4,this.frame5,5,this.frame6,6,this.frame7,7,this.frame8);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextFieldWidth(760);
         this.txt_title.SetTextFit(true);
         this.txt_select.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextSize(30);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextFieldWidth(760);
         this.txt_title.SetTextFit(true);
         this.txt_select.SetTextColor(6974058);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextSize(30);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextFieldWidth(760);
         this.txt_title.SetTextFit(true);
         this.txt_select.SetTextColor(11606272);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextSize(30);
      }
      
      internal function frame4() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextFieldWidth(760);
         this.txt_title.SetTextFit(true);
         this.txt_select.SetTextColor(6974058);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextSize(30);
      }
      
      internal function frame5() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(8773886);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextFieldWidth(760);
         this.txt_title.SetTextFit(true);
         this.txt_select.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextSize(30);
      }
      
      internal function frame6() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextFieldWidth(760);
         this.txt_title.SetTextFit(true);
         this.txt_select.SetTextColor(6974058);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextSize(30);
      }
      
      internal function frame7() : *
      {
         stop();
         this.txt_nomal.SetTextPivot(smb_font.CCD_PIVOT_CC);
      }
      
      internal function frame8() : *
      {
         stop();
         this.txt_nomal.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_nomal.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_nomal.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
   }
}

