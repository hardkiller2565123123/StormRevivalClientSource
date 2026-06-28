package script.hist_cmn_brt
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol27")]
   public class nut_clear extends MovieClip
   {
      
      public var txt_clear:smb_font;
      
      public function nut_clear()
      {
         super();
         addFrameScript(0,this.frame1,29,this.frame30,30,this.frame31);
      }
      
      internal function frame1() : *
      {
         this.txt_clear.SetText("シナリオ達成率：100％");
         this.txt_clear.SetTextSize(28);
         this.txt_clear.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_clear.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_clear.SetTextFieldWidth(320);
         this.txt_clear.SetTextFit(true);
      }
      
      internal function frame30() : *
      {
         this.stop();
      }
      
      internal function frame31() : *
      {
         this.stop();
      }
   }
}

