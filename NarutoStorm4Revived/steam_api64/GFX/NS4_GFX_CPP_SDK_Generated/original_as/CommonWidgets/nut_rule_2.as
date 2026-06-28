package script.net_search
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class nut_rule extends MovieClip
   {
      
      public var txt_rule:smb_font;
      
      public function nut_rule()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_rule.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_rule.SetTextSize(30);
         this.txt_rule.SetTextFieldWidth(450);
         this.txt_rule.SetTextFit(true);
      }
   }
}

