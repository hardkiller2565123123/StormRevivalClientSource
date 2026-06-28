package shop_cos_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol11")]
   public dynamic class anm_head_7 extends MovieClip
   {
      
      public var txt_head_cos:smb_font;
      
      public var txt_head_price:smb_font;
      
      public function anm_head_7()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_head_price.SetText("価格");
         this.txt_head_cos.SetText("コスチューム");
         this.txt_head_cos.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head_cos.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head_cos.SetTextSize(33);
         this.txt_head_price.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head_price.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head_price.SetTextSize(30);
      }
   }
}

