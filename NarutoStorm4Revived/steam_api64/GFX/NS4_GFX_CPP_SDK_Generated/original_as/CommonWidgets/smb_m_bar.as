package script.shop_cos
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class smb_m_bar extends MovieClip
   {
      
      internal static const CCD_ITEM_TXT_MARGIN:Number = -50;
      
      public var dmy_item2:nut_tex00;
      
      public var txt_material:smb_font;
      
      public var txt_own_num:smb_font;
      
      public var txt_req_num:smb_font;
      
      private var m_txtItem:smb_font = null;
      
      private var m_txtReq:smb_font = null;
      
      private var m_txtOwn:smb_font = null;
      
      private var m_dmy:MovieClip = null;
      
      private var m_isChangedLayout:Boolean = false;
      
      public function smb_m_bar()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
         this.m_txtItem = this["txt_material"];
         this.m_txtReq = this["txt_req_num"];
         this.m_txtOwn = this["txt_own_num"];
         this.m_dmy = this["dmy_item2"];
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         var _loc2_:Point = null;
         var _loc3_:Number = NaN;
         var _loc4_:Number = NaN;
         if(this.m_txtItem.IsArabic() == true)
         {
            if(this.m_isChangedLayout == false)
            {
               _loc1_ = new Point();
               _loc2_ = new Point();
               this.m_txtOwn.GetTextPos(_loc1_);
               this.m_txtReq.GetTextPos(_loc2_);
               _loc3_ = Math.abs(_loc1_.x - _loc2_.x);
               this.m_txtItem.GetTextPos(_loc2_);
               _loc4_ = Math.abs(_loc2_.x - this.m_dmy.x);
               this.m_txtItem.SetTextPos(_loc1_.x + CCD_ITEM_TXT_MARGIN,_loc1_.y);
               this.m_txtOwn.SetTextPos(_loc2_.x,_loc2_.y);
               this.m_txtReq.SetTextPos(_loc2_.x + _loc3_,_loc2_.y);
               this.m_dmy.x = _loc1_.x + _loc4_ + CCD_ITEM_TXT_MARGIN;
            }
            this.m_txtItem.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtItem.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtReq.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtOwn.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_isChangedLayout = true;
         }
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_material.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_material.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_material.SetTextSize(30);
         this.txt_req_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_req_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_req_num.SetTextSize(30);
         this.txt_own_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_own_num.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_own_num.SetTextSize(30);
         this.CheckArabicLayout();
         this.txt_material.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_req_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_own_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_material.SetTextColor(14501921);
         this.txt_req_num.SetTextColor(14501921);
         this.txt_own_num.SetTextColor(14501921);
      }
   }
}

