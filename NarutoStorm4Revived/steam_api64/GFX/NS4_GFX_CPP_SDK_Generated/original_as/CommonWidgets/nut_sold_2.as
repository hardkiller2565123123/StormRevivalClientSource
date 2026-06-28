package script.shop_cmn
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_sold extends MovieClip
   {
      
      public var txt_sold:smb_font;
      
      public function nut_sold()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_sold.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_sold.SetTextColor(15920340);
         this.txt_sold.SetTextSize(30);
         this.txt_sold.SetTextFieldWidth(170);
         this.txt_sold.SetTextFit(true);
      }
   }
}

