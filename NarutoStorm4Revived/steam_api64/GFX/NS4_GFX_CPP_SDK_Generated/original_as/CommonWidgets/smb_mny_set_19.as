package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.icon_item.nut_icon_money;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol20")]
   public dynamic class smb_mny_set_19 extends MovieClip
   {
      
      public var mc_icon_money:nut_icon_money;
      
      public var txt_mny01:smb_font;
      
      public function smb_mny_set_19()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_mny01.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_mny01.SetTextSize(30);
      }
   }
}

