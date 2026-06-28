package script.duel_item
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public dynamic class nut_duel_item extends MovieClip
   {
      
      public var dmy_item:nut_tex00;
      
      public var txt_stock:smb_font;
      
      public function nut_duel_item()
      {
         super();
         addFrameScript(0,this.frame1,13,this.frame14,14,this.frame15);
      }
      
      internal function frame1() : *
      {
         this.txt_stock.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_stock.SetTextSize(27);
         this.stop();
      }
      
      internal function frame14() : *
      {
         gotoAndStop("stay");
      }
      
      internal function frame15() : *
      {
         this.stop();
      }
   }
}

