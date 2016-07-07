angular.module('CrudApp', []).config(['$routeProvider', function($routeProvider) {
        $routeProvider.
        when('/', {templateUrl: 'partials/lists.html', controller: ListCtrl}).
        //when('/add-user', {templateUrl: 'assets/tpl/add-new.html', controller: AddCtrl}).
        otherwise({redirectTo: '/'});
    }]);
function ListCtrl($scope, $http) {
    $http.get('app/api/salons').success(function(data) {
        $scope.salons = data;
    });
}
/*
function AddCtrl($scope, $http, $location) {
    $scope.master = {};
    $scope.activePath = null;
    $scope.add_new = function(user, AddNewForm) {
    console.log(user);
    $http.post('api/add_user', user).success(function(){
        $scope.reset();
        $scope.activePath = $location.path('/');
    });
    $scope.reset = function() {
        $scope.user = angular.copy($scope.master);
    };
        $scope.reset();
    };

}*/