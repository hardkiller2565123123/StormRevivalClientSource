package script.shop_list
{
   import flash.display.MovieClip;
   import script.shop_cmn.nut_total;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public class smb_total extends MovieClip
   {
      
      public var all_total:nut_total;
      
      private var m_txtTotal:smb_font = null;
      
      private var m_txtPrice:smb_font = null;
      
      public function smb_total()
      {
         super();
         var _loc1_:MovieClip = this["all_total"];
         this.m_txtTotal = _loc1_["txt_total"];
         this.m_txtPrice = _loc1_["txt_price"];
         if(this.m_txtTotal != null && this.m_txtTotal.IsArabic() == true)
         {
            _loc1_.x -= 1080;
         }
      }
      
      public function SetTextTotal(param1:String) : *
      {
         if(this.m_txtTotal != null)
         {
            this.m_txtTotal.SetText(param1);
         }
      }
      
      public function SetTextPrice(param1:String, param2:String) : *
      {
         var _loc3_:Array = null;
         if(this.m_txtPrice != null)
         {
            _loc3_ = new Array();
            _loc3_.push(param2);
            this.m_txtPrice.SetText(param1,_loc3_);
         }
      }
   }
}

