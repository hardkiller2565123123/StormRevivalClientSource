package script.preset
{
   import flash.display.MovieClip;
   import script.xcmn_unset.smb_win00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol12")]
   public class nut_preset extends MovieClip
   {
      
      public var mc_set00:anm_set00;
      
      public var mc_set01:anm_set00;
      
      public var mc_help:MovieClip;
      
      public var mc_win00:smb_win00;
      
      public var mc_set06:anm_set00;
      
      public var mc_set07:anm_set00;
      
      public var mc_set04:anm_set00;
      
      public var mc_set05:anm_set00;
      
      public var mc_set02:anm_set00;
      
      public var mc_set03:anm_set00;
      
      private var m_slotMCList:Array;
      
      public function nut_preset()
      {
         var _loc2_:String = null;
         var _loc3_:anm_set00 = null;
         super();
         addFrameScript(7,this.frame8,14,this.frame15);
         this.m_slotMCList = new Array(define.SLOT_NUM);
         var _loc1_:int = 0;
         while(_loc1_ < define.SLOT_NUM)
         {
            _loc2_ = "mc_set0" + _loc1_.toString();
            _loc3_ = this[_loc2_];
            this.m_slotMCList[_loc1_] = _loc3_;
            _loc3_.SetIndexNumber(_loc1_ + 1);
            _loc3_.SetCursorOff();
            _loc1_++;
         }
      }
      
      public function Initialize(param1:Array) : *
      {
         var _loc3_:anm_set00 = null;
         var _loc2_:int = 0;
         while(_loc2_ < define.SLOT_NUM)
         {
            _loc3_ = this.m_slotMCList[_loc2_];
            _loc3_.SetSlotData(param1[_loc2_]);
            _loc2_++;
         }
      }
      
      public function UpdateCursor(param1:int, param2:int) : *
      {
         var _loc3_:anm_set00 = null;
         if(param1 >= 0 && param1 < define.SLOT_NUM)
         {
            _loc3_ = this.m_slotMCList[param1];
            _loc3_.SetCursorOff();
         }
         if(param2 >= 0 && param2 < define.SLOT_NUM)
         {
            _loc3_ = this.m_slotMCList[param2];
            _loc3_.SetCursorOn();
         }
      }
      
      public function UpdateCursorDecide(param1:int) : *
      {
         var _loc2_:anm_set00 = null;
         if(param1 >= 0 && param1 < define.SLOT_NUM)
         {
            _loc2_ = this.m_slotMCList[param1];
            _loc2_.SetCursorSelect();
         }
      }
      
      public function RequestOut() : *
      {
         this.gotoAndPlay("out");
      }
      
      public function GetSlotMC(param1:int) : anm_set00
      {
         var _loc2_:anm_set00 = null;
         if(param1 >= 0 && param1 < define.SLOT_NUM)
         {
            _loc2_ = this.m_slotMCList[param1];
         }
         return _loc2_;
      }
      
      internal function frame8() : *
      {
         stop();
      }
      
      internal function frame15() : *
      {
         stop();
      }
   }
}

