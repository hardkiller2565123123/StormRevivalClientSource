package script.freebtl_prac_win
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_win3.smb_win3;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class nut_prac_win extends MovieClip
   {
      
      public var mc_bg:smb_win3;
      
      public var mc_rslt_ok:MovieClip;
      
      public var txt_cont:smb_font;
      
      public var txt_title:smb_font;
      
      public function nut_prac_win()
      {
         super();
         addFrameScript(6,this.frame7,12,this.frame13);
      }
      
      internal function frame7() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextColor(10165790);
         this.txt_title.SetTextSize(33);
         this.txt_cont.SetTextFieldWidth(900);
         this.txt_cont.SetTextWordWrap(true);
         this.txt_cont.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_cont.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_cont.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_cont.SetTextSize(33);
      }
      
      internal function frame13() : *
      {
         stop();
      }
   }
}

