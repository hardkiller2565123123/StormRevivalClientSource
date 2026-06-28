package script.start_change
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base4;
   import script.xcmn_menu.nut_cursor_m;
   import script.xcmn_menu.nut_line;
   import script.xcmn_menu.nut_sel1;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_shift extends MovieClip
   {
      
      public var all_line:nut_line;
      
      public var dmy_event:nut_tex00;
      
      public var mc_cursor:nut_cursor_m;
      
      public var mc_sel:nut_sel1;
      
      public var txt_event:smb_font;
      
      public var dmy_char:nut_tex00;
      
      public var dmy_name:nut_tex00;
      
      public var all_base4:nut_base4;
      
      public var txt_per:smb_font;
      
      public function nut_shift()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_event.SetTextSize(33);
         this.txt_event.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_event.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_event.SetDropShadowFilter(smb_font.CCD_COLOR_WHITE);
         this.txt_per.SetTextSize(28);
         this.txt_per.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_per.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_per.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_per.SetTextFieldWidth(360);
         this.txt_per.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
         this.stop();
         this.txt_event.SetTextSize(33);
         this.txt_event.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_event.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_event.SetDropShadowFilter(smb_font.CCD_COLOR_WHITE);
         this.txt_per.SetTextSize(28);
         this.txt_per.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_per.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_per.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_per.SetTextFieldWidth(360);
         this.txt_per.SetTextFit(true);
      }
   }
}

