package script.stagesel
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol13")]
   public dynamic class nut_title extends MovieClip
   {
      
      public var txt_stagetitle:smb_font;
      
      public function nut_title()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_stagetitle.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_stagetitle.SetTextSize(45);
         this.txt_stagetitle.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_stagetitle.SetDropShadowFilter(14939319);
         this.txt_stagetitle.SetTextFieldWidth(1175);
         this.txt_stagetitle.SetTextFit(true);
      }
   }
}

