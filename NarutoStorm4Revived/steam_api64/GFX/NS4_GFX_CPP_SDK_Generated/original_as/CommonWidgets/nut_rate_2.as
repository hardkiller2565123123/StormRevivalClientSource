package script.hist_cmn_brt
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol26")]
   public class nut_rate extends MovieClip
   {
      
      public var txt_rate:smb_font;
      
      public function nut_rate()
      {
         super();
         addFrameScript(0,this.frame1,29,this.frame30,30,this.frame31);
      }
      
      internal function frame1() : *
      {
         this.txt_rate.SetText("Ｓランク達成率：100％");
         this.txt_rate.SetTextSize(25);
         this.txt_rate.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_rate.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_rate.SetTextFieldWidth(300);
         this.txt_rate.SetTextFit(true);
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

