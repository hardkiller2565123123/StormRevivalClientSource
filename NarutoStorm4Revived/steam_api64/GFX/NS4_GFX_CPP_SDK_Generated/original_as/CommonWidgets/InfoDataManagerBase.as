package script.infoData
{
   public class InfoDataManagerBase
   {
      
      public var m_dataList:Array;
      
      public var m_newIconCheckItemKeyList:Array;
      
      public function InfoDataManagerBase()
      {
         super();
         this.m_newIconCheckItemKeyList = new Array();
      }
      
      public function GetNewIconOffItemKeyList() : Array
      {
         var _loc4_:InfoDataBase = null;
         var _loc1_:Array = new Array();
         var _loc2_:int = int(this.m_dataList.length);
         var _loc3_:int = 0;
         while(_loc3_ < _loc2_)
         {
            _loc4_ = this.m_dataList[_loc3_];
            if(this.IsNewIconCheck(_loc4_.m_saveIdx) && _loc4_.m_isNew == false)
            {
               _loc1_.push(_loc4_.m_saveIdx);
            }
            _loc3_++;
         }
         return _loc1_;
      }
      
      public function IsNewIconCheck(param1:uint) : Boolean
      {
         var _loc2_:Boolean = false;
         var _loc3_:int = int(this.m_newIconCheckItemKeyList.length);
         var _loc4_:int = 0;
         while(_loc4_ < _loc3_)
         {
            if(this.m_newIconCheckItemKeyList[_loc4_] == param1)
            {
               _loc2_ = true;
               break;
            }
            _loc4_++;
         }
         return _loc2_;
      }
   }
}

